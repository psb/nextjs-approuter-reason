type request;
[@bs.val] external request: request = "request";
[@bs.send] external request_json: request => Js.Promise.t(Js_json.t) = "json";

type t;
type message = {message: string};
type status = {status: int};
type response;
[@bs.module "next/server"] external response: response = "NextResponse";
[@bs.send] external response_json: (response, message, status) => t = "json";
