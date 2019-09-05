open ReactNavigation;
open ReactNative;

let styles =
  Style.(
    style(
      ~backgroundColor=
        Platform.os == Platform.android
          ? Constants.Colours.primaryColour : "white",
      (),
    )
  );
module Container =
  AppContainer.Make({
    let config =
      StackNavigator.config(
        ~defaultNavigationOptions=
          StackNavigator.navigationStackScreenOptions(
            ~headerStyle=styles,
            ~headerTintColor=
              Platform.os == Platform.android
                ? "white" : Constants.Colours.primaryColour,
            (),
          ),
        (),
      );

    type screenProps = unit;

    let navigator =
      StackNavigator.makeWithConfig(
        {
          "Categories": {
            screen: Screens.Categories.make,
          },
          "CategoryMeals": {
            screen: Screens.CategoryMeals.make,
          },
          "MealDetail": {
            screen: Screens.MealDetail.make,
          },
        },
        config,
      );
  });

[@react.component]
let make = () => <Container />;