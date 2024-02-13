#include "SubmitAnswerRequest.h"

using namespace Requests;

const char* SubmitAnswerRequest::k_answerId = "answer_id";

/***************************************************************
 @ brief: nlohmann to_json for SubmitAnswerRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::to_json(json& outputJson, const SubmitAnswerRequest& submitAnswerRequestToConvert)
{
    outputJson = json{ { SubmitAnswerRequest::k_answerId, submitAnswerRequestToConvert.answerId } };
}

/***************************************************************
 @ brief: nlohmann from_json for SubmitAnswerRequest
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Requests::from_json(const json& jsonToConvert, SubmitAnswerRequest& outputSubmitAnswerRequest)
{
    jsonToConvert.at(SubmitAnswerRequest::k_answerId).get_to(outputSubmitAnswerRequest.answerId);
}
