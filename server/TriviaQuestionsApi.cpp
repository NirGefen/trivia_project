#include "TriviaQuestionsApi.h"

const std::wstring TriviaQuestionsApi::URL = L"https://opentdb.com/"; /* The URL of the used API */
const std::wstring TriviaQuestionsApi::API_PATH = L"/api.php"; /* path of main query */
const std::wstring TriviaQuestionsApi::PARAM_AMOUNT = L"amount"; /* question amount key */
const std::wstring TriviaQuestionsApi::PARAM_DIFFICULTY = L"difficulty"; /* question difficulty level key (in this version we only care about "medium". there are other possible values too */
const std::wstring TriviaQuestionsApi::PARAM_TYPE = L"type"; /* question type key. we only support "multiple" */
const std::wstring TriviaQuestionsApi::TYPE = L"multiple";
const unsigned int TriviaQuestionsApi::MAX_AMOUNT = 50; /* maximum possible amount of questions to be queried per query */


/***************************************************************
 @ brief: queries and returns a list of question, the demanded size of which is given
 [>>] unsigned int amount: the amount of questions to query (not limited by TriviaQuestionsApi::MAX_AMOUNT, could be any positive reasonable amount)
 [<<] std::list<Question>: the list of queried questions
****************************************************************/
std::list<Trivia::Question> TriviaQuestionsApi::getQuestions(unsigned int amount)
{
	json currentQueryResult;
	std::list<Trivia::Question> questionList;
	while (amount > 0)
	{
		currentQueryResult = TriviaQuestionsApi::query(amount);
		for (const json& questionJson : currentQueryResult["results"])
		{

			questionList.push_back(questionJson.get<Trivia::Question>());
		}
		amount = (amount > TriviaQuestionsApi::MAX_AMOUNT) ? amount - TriviaQuestionsApi::MAX_AMOUNT : 0;  // avoid overflow
	}
	return questionList;
}

/***************************************************************
 @ brief: raw query, unprocessed json output with max amount being 50
 [>>] unsigned int amount: amount of questions to query (max is TriviaQuestionsApi::MAX_AMOUNT). if > TriviaQuestionsApi::MAX_AMOUNT then TriviaQuestionsApi::MAX_AMOUNT will be queried instead.
 [>>] const std::wstring& difficulty: the difficulty levels of the questions to query, defaults to "medium"
 [<<] json: the queried json
****************************************************************/
json TriviaQuestionsApi::query(unsigned int amount, const std::wstring& difficulty)
{
	web::http::client::http_client client = web::http::client::http_client(web::uri(TriviaQuestionsApi::URL));
	web::http::uri_builder builder(TriviaQuestionsApi::API_PATH);

	builder.append_query(TriviaQuestionsApi::PARAM_AMOUNT, std::to_wstring(amount));
	builder.append_query(TriviaQuestionsApi::PARAM_DIFFICULTY, difficulty);
	builder.append_query(TriviaQuestionsApi::PARAM_TYPE, TriviaQuestionsApi::TYPE);
	amount = std::min(amount, TriviaQuestionsApi::MAX_AMOUNT);

	pplx::task<json> queryTask = client.request(web::http::methods::GET, builder.to_string()).then(
		[=](web::http::http_response response) {
			auto reqBodyStream = response.body();
			concurrency::streams::stringstreambuf sbuffer;
			auto& target = sbuffer.collection();
			reqBodyStream.read_to_end(sbuffer).get();
			return json::parse(target);
		});
	return queryTask.get();
}
