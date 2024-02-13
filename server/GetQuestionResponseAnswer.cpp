#include "GetQuestionResponseAnswer.h"

using namespace Responses;

const char* GetQuestionResponseAnswer::k_answerId = "answer_id";
const char* GetQuestionResponseAnswer::k_answer = "answer";
/***************************************************************
 @ brief: nlohmann to_json for GetQuestionResponseAnswer
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetQuestionResponseAnswer& getQuestionResponseAnswerToConvert)
{
    outputJson = json{ { GetQuestionResponseAnswer::k_answer, getQuestionResponseAnswerToConvert.answer },
                       { GetQuestionResponseAnswer::k_answerId, getQuestionResponseAnswerToConvert.answerId } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetQuestionResponseAnswer
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetQuestionResponseAnswer& outputGetQuestionResponseAnswer)
{
    jsonToConvert.at(GetQuestionResponseAnswer::k_answer).get_to(outputGetQuestionResponseAnswer.answer);
    jsonToConvert.at(GetQuestionResponseAnswer::k_answerId).get_to(outputGetQuestionResponseAnswer.answerId);
}
