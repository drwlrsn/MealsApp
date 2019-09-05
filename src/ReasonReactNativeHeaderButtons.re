module HeaderButton = {
  [@bs.module "react-navigation-header-buttons"] [@react.component]
  // HeaderButtonProps
  external make:
    (
      ~_IconComponent: React.componentLike(
                         {
                           .
                           "color": option(string),
                           "size": option(float),
                           "name": string,
                         },
                         React.element,
                       )
                         =?,
      ~iconSize: float=?,
      ~color: string=?
    ) =>
    React.element =
    "HeaderButton";
};

module Item = {
  [@bs.module "react-navigation-header-buttons"] [@react.component]
  external make:
    (
      ~title: string,
      ~testID: string=?,
      ~onPress: unit => unit=?,
      ~show: [@bs.string] [ | `always | `never]=?,
      ~_ButtonElement: React.element=?,
      ~iconName: string=?,
      ~buttonStyle: ReactNative.Style.t=?,
      ~buttonWrapperStyle: ReactNative.Style.t=?
    ) =>
    React.element =
    "Item";
};

module HeaderButtons = {
  [@bs.module "react-navigation-header-buttons"] [@react.component]
  external make:
    (
      ~left: bool=?,
      ~_HeaderButtonComponent: React.componentLike(Js.t('a), React.element),
      ~children: React.element,
      ~overFlowButtonWrapperStyle: ReactNative.Style.t=?,
      ~overFlowButtonTestID: string=?,
      // OverFlowButtonProps
      // ~onOverflowMenuPress: (
      //                         array(React.element),
      //                         ReactNative.View.element,
      //                         string
      //                       ) =>
      //                       unit,
      ~_OverflowIcon: React.element=?
    ) =>
    React.element =
    "HeaderButtons";
};