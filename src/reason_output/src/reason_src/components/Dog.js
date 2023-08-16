// Generated by Melange

import * as Curry from "melange.runtime/curry.js";
import * as React from "react";
import * as Json__Json_decode from "melange-json/./Json_decode.js";

function decodeFetchResult(json) {
  return {
          message: Json__Json_decode.field("message", Json__Json_decode.string, json),
          status: Json__Json_decode.field("status", Json__Json_decode.string, json)
        };
}

function Dog(Props) {
  var match = React.useReducer((function (state, action) {
          if (action) {
            return {
                    data: action._0,
                    loading: false
                  };
          } else {
            return {
                    data: state.data,
                    loading: true
                  };
          }
        }), {
        data: {
          message: "https://images.dog.ceo/breeds/rottweiler/n02106550_10478.jpg",
          status: "success"
        },
        loading: false
      });
  var dispatch = match[1];
  var state = match[0];
  var loadingImage = function (param) {
    return React.createElement("img", {
                alt: "dog",
                src: "/dog.svg"
              });
  };
  var dogImage = function (data) {
    return React.createElement("img", {
                className: "mx-auto",
                alt: data.status !== "success" ? "error dog" : "dog",
                src: data.status !== "success" ? "/500.jpg" : data.message
              });
  };
  var buttons = function (param) {
    return React.createElement("div", {
                className: "flex justify-around"
              }, React.createElement("a", {
                    className: "rounded-md p-4 mt-2 bg-slate-400 text-white hover:bg-slate-500",
                    href: "/"
                  }, "Home"), React.createElement("button", {
                    className: "rounded-md p-4 mt-2 bg-green-500 text-white hover:bg-green-600",
                    onClick: (function (param) {
                        Curry._1(dispatch, /* Loading */0);
                        var callback = function (data) {
                          Curry._1(dispatch, /* Loaded */{
                                _0: data
                              });
                        };
                        fetch("https://dog.ceo/api/breeds/image/random").then(function (prim) {
                                  return prim.json();
                                }).then(function (json) {
                                var data = decodeFetchResult(json);
                                Curry._1(callback, data);
                                return Promise.resolve(undefined);
                              }).catch(function (err) {
                              console.log("Error", err);
                              Curry._1(callback, {
                                    message: "",
                                    status: "error"
                                  });
                              return Promise.resolve(undefined);
                            });
                      })
                  }, "Fetch another image"));
  };
  return React.createElement("div", {
              className: "container mx-auto max-w-md text-center p-4"
            }, state.loading ? loadingImage(undefined) : React.createElement(React.Fragment, undefined, dogImage(state.data), buttons(undefined)));
}

var make = Dog;

export {
  make ,
}
/* react Not a pure module */
