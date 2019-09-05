open ReactNative;
open ReactNavigation;
open Domain;
open Components;

let rs = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen":
        style(~flex=1., ~justifyContent=`center, ~alignItems=`center, ()),
    })
  );

module Categories = {
  let styles =
    Style.(
      StyleSheet.create({
        "gridItem": style(~flex=1., ~margin=15.->dp, ~height=150.->dp, ()),
      })
    );

  [@react.component]
  let make = (~navigation) => {
    let renderGridItem =
        (itemData: ReactNative.VirtualizedList.renderItemProps(category)) =>
      <CategoryGridTile
        onSelect={_ =>
          navigation->Navigation.navigateWithParams(
            "CategoryMeals",
            {"categoryId": itemData##item.id},
          )
        }
        title={itemData##item.title}
        color={itemData##item.color}
      />;

    <FlatList
      numColumns=2
      data={DummyData.categories->Belt.Map.String.valuesToArray}
      renderItem=renderGridItem
      keyExtractor={(v, _) => v.id}
    />;
  };

  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Meal Categories", ()),
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
  let getCategory = (navigation, p) =>
    navigation
    ->Navigation.getParam(p)
    ->Js.Nullable.toOption
    ->Belt.Option.flatMap(catId =>
        DummyData.categories->Belt.Map.String.get(catId)
      );
  [@react.component]
  let make = (~navigation) => {
    let category = navigation->getCategory("categoryId");

    let displayedMeals =
      switch (category) {
      | None => [||]
      | Some(c) =>
        DummyData.meals
        ->Belt.Map.String.valuesToArray
        ->Belt.Array.keep(m =>
            m.categoryIds->Belt.Array.some(cat => cat == c.id)
          )
      };

    // let displayedMeals2 =
    //   category->Belt.Option.mapWithDefault([||], c =>
    //     DummyData.meals
    //     ->Belt.Map.String.valuesToArray
    //     ->Belt.Array.keep(m =>
    //         m.categoryIds->Belt.Array.some(cat => cat == c.id)
    //       )
    //   );

    let renderMealItem = itemData =>
      <MealItem
        item=itemData##item
        onSelectMeal={_ =>
          navigation->Navigation.navigateWithParams(
            "MealDetail",
            {"mealId": itemData##item.id},
          )
        }
      />;

    <View style=styles##screen>
      <FlatList
        data=displayedMeals
        keyExtractor={(item, _index) => item.id}
        renderItem=renderMealItem
        style=Style.(style(~width=100.->pct, ()))
      />
    </View>;
  };

  make->NavigationOptions.setDynamicNavigationOptions(params =>
    NavigationOptions.t(
      ~title=
        params##navigation
        ->getCategory("categoryId")
        ->Belt.Option.mapWithDefault("Missing", v => v.title),
      (),
    )
  );
};

module MealDetail = {
  let getMeal = m =>
    m
    ->Js.Nullable.toOption
    ->Belt.Option.flatMap(v => DummyData.meals->Belt.Map.String.get(v));
  [@react.component]
  let make = (~navigation) => {
    let meal = navigation->Navigation.getParam("mealId")->getMeal;
    <View style=styles##screen>
      <Text>
        {(
           "MealId "
           ++ meal->Belt.Option.mapWithDefault("missing", v => v.title)
         )
         ->rs}
      </Text>
      <Button title="Go Back" onPress={_ => navigation->Navigation.popToTop} />
    </View>;
  };
  make->NavigationOptions.setDynamicNavigationOptions(params =>
    NavigationOptions.t(
      ~title=
        params##navigation
        ->Navigation.getParam("mealId")
        ->getMeal
        ->Belt.Option.mapWithDefault("Whoops!", v => v.title),
      ~headerRight=
        <ReasonReactNativeHeaderButtons.HeaderButtons
          _HeaderButtonComponent=Components.CustomHeaderButton.make>
          <ReasonReactNativeHeaderButtons.Item
            title="favourite"
            iconName="star"
          />
        </ReasonReactNativeHeaderButtons.HeaderButtons>,
      //      ~headerRight=<Icons.AntDesign name="star" />,
      (),
    )
  );
};