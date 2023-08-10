[@bs.config {flags: [|"--preamble", "\"use client\";"|]}];

open Components;

[@react.component]
let default = () => {
  <Joke />;
};
