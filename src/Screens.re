open ReactNative;
open ReactNavigation;

let rs = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen":
        style(~flex=1., ~justifyContent=`center, ~alignItems=`center, ()),
    })
  );

module Categories = {
  [@react.component]
  let make = (~navigation) =>
    <View style=styles##screen>
      <Text> "Categories"->rs </Text>
      <Button
        title="Go to Meals!"
        onPress={_ => navigation->Navigation.navigate("CategoryMeals")}
      />
    </View>;

  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Categories", ()),
  );
};

module Filters = {
  [@react.component]
  let make = () =>
    <View style=styles##screen> <Text> "Filters"->rs </Text> </View>;
  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Filters", ()),
  );
};

module Favourites = {
  [@react.component]
  let make = () =>
    <View style=styles##screen> <Text> "Favourites"->rs </Text> </View>;
  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Favourites", ()),
  );
};

module CategoryMeals = {
  [@react.component]
  let make = () =>
    <View style=styles##screen> <Text> "CategoryMeals"->rs </Text> </View>;
  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(
      ~title="Category",
      ~headerTitle=
        ReactNavigation.NavigationOptions.HeaderTitle.string("Meals"),
      (),
    ),
  );
};

module MealDetail = {
  [@react.component]
  let make = (~navigation) =>
    <View style=styles##screen> <Text> "MealDetail"->rs </Text> </View>;
  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Meal", ()),
  );
};