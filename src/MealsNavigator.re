open ReactNavigation;

module Container =
  AppContainer.Make({
    type screenProps = unit;

    let navigator =
      StackNavigator.make({
        "Categories": Screens.Categories.make,
        "CategoryMeals": {
          screen: Screens.CategoryMeals.make,
        },
        "MealDetail": Screens.MealDetail.make,
      });
  });

[@react.component]
let make = () => <Container />;