#include "SubmitAnswerResponse.h"

using namespace Responses;

const char* SubmitAnswerResponse::k_status = "status";
const char* SubmitAnswerResponse::k_correctAnswerId = "correct_answer_id";

/***************************************************************
 @ brief: nlohmann to_json for SubmitAnswerResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const SubmitAnswerResponse& submitAnswerResponseToConvert)
{
    outputJson = json{ { SubmitAnswerResponse::k_status, submitAnswerResponseToConvert.status },
                       { SubmitAnswerResponse::k_correctAnswerId, submitAnswerResponseToConvert.correctAnswerId } };
}

/***************************************************************
 @ brief: nlohmann from_json for SubmitAnswerResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, SubmitAnswerResponse& outputSubmitAnswerResponse)
{
    jsonToConvert.at(SubmitAnswerResponse::k_status).get_to(outputSubmitAnswerResponse.status);
    jsonToConvert.at(SubmitAnswerResponse::k_correctAnswerId).get_to(outputSubmitAnswerResponse.correctAnswerId);
}
