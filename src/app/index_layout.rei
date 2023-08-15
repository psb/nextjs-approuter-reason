type metadata = {
  title: string,
  description: string,
};
let metadata: metadata;

[@react.component]
let make: (~children: React.element) => React.element;
