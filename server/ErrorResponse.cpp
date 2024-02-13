#include "ErrorResponse.h"

using namespace Responses;

const char* ErrorResponse::k_message = "message";

/***************************************************************
 @ brief: nlohmann to_json for ErrorResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const Responses::ErrorResponse& ErrorResponseToConvert)
{
	outputJson = json{ { ErrorResponse::k_message, ErrorResponseToConvert.message } };
}

/***************************************************************
 @ brief: nlohmann from_json for ErrorResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, Responses::ErrorResponse& outputErrorResponse)
{
	jsonToConvert.at(ErrorResponse::k_message).get_to(outputErrorResponse.message);
}
