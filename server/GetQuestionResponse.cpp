#include "GetQuestionResponse.h"

using namespace Responses;

const char* GetQuestionResponse::k_status = "status";
const char* GetQuestionResponse::k_question = "question";
const char* GetQuestionResponse::k_answers = "answers";
const char* GetQuestionResponse::k_category = "category";

/***************************************************************
 @ brief: nlohmann to_json for GetQuestionResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetQuestionResponse& getQuestionResponseToConvert)
{
    outputJson = json{ { GetQuestionResponse::k_status, getQuestionResponseToConvert.status },
                       { GetQuestionResponse::k_question, getQuestionResponseToConvert.question }, 
                       { GetQuestionResponse::k_answers, getQuestionResponseToConvert.answers },
                       { GetQuestionResponse::k_category, getQuestionResponseToConvert.category } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetQuestionResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetQuestionResponse& outputGetQuestionResponse)
{
    jsonToConvert.at(GetQuestionResponse::k_status).get_to(outputGetQuestionResponse.status);
    jsonToConvert.at(GetQuestionResponse::k_question).get_to(outputGetQuestionResponse.question);
    jsonToConvert.at(GetQuestionResponse::k_answers).get_to(outputGetQuestionResponse.answers);
    jsonToConvert.at(GetQuestionResponse::k_category).get_to(outputGetQuestionResponse.category);
}
