open ReactNative;
open Expo;

let fetchFonts = () =>
  Font.loadAsync([
    ("open-sans", Packager.require("../assets/OpenSans-Regular.ttf")),
    ("open-sans-bold", Packager.require("../assets/OpenSans-Bold.ttf")),
  ]);

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(
          ~flex=1.,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor="#F5FCFF",
          (),
        ),
      "instructions": style(~textAlign=`center, ~color="#ffffff", ()),
    })
  );

[@react.component]
let app = () => {
  let (appLoaded, setAppLoaded) = React.useState(() => false);
  appLoaded
    ? <MealsNavigator />
    : <AppLoading
        startAsync=fetchFonts
        onFinish={() => setAppLoaded(_ => true)}
      />;
};