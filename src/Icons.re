module AntDesign = {
  [@bs.module "@expo/vector-icons"] [@react.component]
  external make:
    (~name: string, ~size: float=?, ~color: string=?) => React.element =
    "AntDesign";
};