// [%%bs.raw "require('isomorphic-fetch')"];
// [%%bs.raw "require('isomorphic-fetch')"];

// module D = Bs_decoders.Decoders_bs.Decode;

// type request;
// [@bs.module "next/server"] external nextRequest: unit => request = "NextRequest";

// type response;
// [@bs.module "next/server"] external nextRequest: unit => request = "NextRequest";

// [@bs.send] external loginWithRedirect: hook => unit = "loginWithRedirect";
// [@bs.send] external logout: hook => unit = "logout";

// type user;
// [@bs.get] external user: hook => user = "user";
// [@bs.get] external name: user => string = "name";
// [@bs.get] external nickname: user => string = "nickname";
// [@bs.get] external email: user => string = "email";
// [@bs.get] external emailVerified: user => bool = "email_verified";

// [@bs.get] external isAuthenticated: hook => bool = "isAuthenticated";
// [@bs.get] external isLoading: hook => bool = "isLoading";

type event = {
  .
  "path": string,
  "httpMethod": string,
  "headers": Js.Dict.t(string),
  "queryStringParameters": Js.Dict.t(string),
  "body": Js.Json.t,
  "isBase64Encoded": bool,
};

type context = unit;

type response = {
  statusCode: int,
  body: string,
};

type joke_count = {count: int};

type joke_result = {
  joke: string,
  id: string,
  status: int,
};

let decodeJokeCount = (string): joke_count => {
  let json = Json.parse(string);
  switch (json) {
  | Some(j) => Json.Decode.{count: j |> field("count", int)}
  | None => {count: 0}
  };
};

let decodeJoke = (json): joke_result =>
  Json.Decode.{
    joke: json |> field("joke", string),
    status: json |> field("status", int),
    id: json |> field("id", string),
  };

// let jokeCountDecoder: D.decoder(joke_count) =
//   D.(field("count", int) >>= (count => succeed({count: count})));

// let jokeDecoder: D.decoder(joke_result) =
//   D.(
//     field("joke", string)
//     >>= (
//       joke =>
//         field("id", string)
//         >>= (
//           id =>
//             field("status", int) >>= (status => succeed({joke, id, status}))
//         )
//     )
//   );
type request;
[@bs.val] external request: request = "request";
[@bs.get] external get_body: request => string = "body";

// module NextResponse = {
// [@bs.module "next/server"] external nextRequest: unit => request = "NextRequest";
type t;
type message = {message: string};
type status = {status: int};
type next_response;
[@bs.module "next/server"]
external next_response: next_response = "NextResponse";
[@bs.send] external next_json: (next_response, message, status) => t = "json";
// };

let handler = request => {
  let jokeCount = decodeJokeCount(get_body(request));
  Js.log2("jokeCount", jokeCount);

  Js.Promise.(
    Fetch.fetchWithInit(
      "https://icanhazdadjoke.com/",
      Fetch.RequestInit.make(
        ~method_=Get,
        ~headers=
          Fetch.HeadersInit.make({
            "Accept": "application/json",
            "User-Agent": "astro-reason (https://github.com/psb/astro-reason)",
          }),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => {
         Js.log2("json", json);
         let data = decodeJoke(json);
         let body =
           Js.Json.stringify(
             Obj.magic({
               "joke": data.joke,
               "count": jokeCount.count + 1,
               "status": data.status,
             }),
           );
         //  resolve(callback(. None, {statusCode: 200, body}, ()));
         resolve(next_json(next_response, {message: body}, {status: 200}));
       })
    |> catch(err => {
         Js.log2("server Error Json", err);
         let body =
           Js.Json.stringify(
             Obj.magic({
               "joke": err,
               "count": jokeCount.count,
               "status": 500,
             }),
           );
         //  resolve(callback(. None, {statusCode: 500, body}, ()));
         resolve(next_json(next_response, {message: body}, {status: 500}));
       })
  );
};

[%%bs.raw {|export const POST = handler|}];
// let handler = (event, _context, callback) => {
//   // let jokeCount = D.decode_string(jokeCountDecoder, event.body);
//   let jokeCount = decodeJokeCount(event.body);
//   Js.log2("jokeCount", jokeCount);

//   Js.Promise.(
//     Fetch.fetchWithInit(
//       "https://icanhazdadjoke.com/",
//       Fetch.RequestInit.make(
//         ~method_=Get,
//         ~headers=
//           Fetch.HeadersInit.make({
//             "Accept": "application/json",
//             "User-Agent": "astro-reason (https://github.com/psb/astro-reason)",
//           }),
//         (),
//       ),
//     )
//     |> then_(Fetch.Response.json)
//     |> then_(json => {
//          Js.log2("json", json);
//          let data = decodeJoke(json);
//          let body =
//            Js.Json.stringify(
//              Obj.magic({
//                "joke": data.joke,
//                "count": jokeCount.count + 1,
//                "status": data.status,
//              }),
//            );
//          resolve(callback(. None, {statusCode: 200, body}, ()));
//        })
//     |> catch(err => {
//          Js.log2("server Error Json", err);
//          let body =
//            Js.Json.stringify(
//              Obj.magic({
//                "joke": err,
//                "count": jokeCount.count,
//                "status": 500,
//              }),
//            );
//          resolve(callback(. None, {statusCode: 500, body}, ()));
//        })
//   );
// |> then_(json => {
//      //  Js.log2("json", json);
//      let data = D.decode_value(jokeDecoder, json);
//      let body = {
//        switch (data, jokeCount) {
//        | (Ok(d), Ok(jc)) =>
//          Js.Json.stringify(
//            Obj.magic({
//              "joke": d.joke,
//              "count": jc.count + 1,
//              "status": d.status,
//            }),
//          )
//        | (Ok(d), Error(ejc)) =>
//          Js.Json.stringify(
//            Obj.magic({
//              "joke": d.joke,
//              "count": D.string_of_error(ejc),
//              "status": d.status,
//            }),
//          )
//        | (Error(ed), Ok(jc)) =>
//          Js.Json.stringify(
//            Obj.magic({
//              "joke": D.string_of_error(ed),
//              "count": jc.count,
//              "status": 500,
//            }),
//          )
//        | (Error(ed), Error(ejc)) =>
//          Js.Json.stringify(
//            Obj.magic({
//              "joke": D.string_of_error(ed),
//              "count": D.string_of_error(ejc),
//              "status": 500,
//            }),
//          )
//        };
//      };
//      resolve(callback(. None, {statusCode: 200, body}, ()));
//    })
// |> catch(err => {
//      Js.log2("server Error Json", err);
//      let body =
//        Js.Json.stringify(
//          Obj.magic({
//            "joke": err,
//            "count":
//              switch (jokeCount) {
//              | Ok(jc) => string_of_int(jc.count)
//              | Error(ejc) => D.string_of_error(ejc)
//              },
//            "status": 500,
//          }),
//        );
//      resolve(callback(. None, {statusCode: 500, body}, ()));
//    })
// };
