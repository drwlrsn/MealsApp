open ReactNative;
open Domain;

module CategoryGridTile = {
  let styles =
    Style.(
      StyleSheet.create({
        "gridItem":
          style(
            ~flex=1.,
            ~margin=15.->dp,
            ~height=150.->dp,
            ~borderRadius=10.,
            ~overflow=`hidden,
            (),
          ),
        "container":
          style(
            ~flex=1.,
            ~borderRadius=10.,
            ~shadowColor="black",
            ~shadowOpacity=0.26,
            ~shadowOffset=offset(~width=0., ~height=2.),
            ~shadowRadius=10.,
            ~elevation=3.,
            ~padding=15.->dp,
            ~justifyContent=`flexEnd,
            ~alignItems=`flexEnd,
            (),
          ),
        "title":
          style(
            ~fontFamily="open-sans-bold",
            ~fontSize=20.,
            ~textAlign=`right,
            (),
          ),
      })
    );

  module TouchableCmp = {
    let defaultStyle = Style.style(~flex=1., ());
    [@react.component]
    let make = (~onPress, ~children, ~style) => {
      let style = StyleSheet.flatten([|style, defaultStyle|]);
      Platform.os == Platform.android && Platform.version >= 21.
        ? <View style>
            <TouchableNativeFeedback onPress>
              children
            </TouchableNativeFeedback>
          </View>
        : <TouchableOpacity style onPress> children </TouchableOpacity>;
    };
  };

  [@react.component]
  let make = (~title, ~onSelect, ~color) =>
    <TouchableCmp onPress=onSelect style=styles##gridItem>
      <View
        style={StyleSheet.flatten([|
          styles##container,
          Style.style(~backgroundColor=color, ()),
        |])}>
        <Text style=styles##title numberOfLines=2> title->React.string </Text>
      </View>
    </TouchableCmp>;
};

module MealItem = {
  let styles =
    Style.(
      StyleSheet.create({
        "mealRow": style(~flexDirection=`row, ()),
        "mealItem":
          style(
            ~height=200.->dp,
            ~width=100.->pct,
            ~backgroundColor="#f5f5f5",
            ~borderRadius=10.,
            ~overflow=`hidden,
            (),
          ),
        "mealHeader": style(~height=85.->pct, ()),
        "mealDetail":
          style(
            ~paddingHorizontal=10.->dp,
            ~justifyContent=`spaceBetween,
            ~alignItems=`center,
            ~height=15.->pct,
            (),
          ),
        "bgImage":
          style(
            ~width=100.->pct,
            ~height=100.->pct,
            ~justifyContent=`flexEnd,
            (),
          ),
        "title":
          style(
            ~fontFamily="open-sans-bold",
            ~fontSize=22.,
            ~color="white",
            ~textAlign=`center,
            (),
          ),
        "titleContainer":
          style(
            ~backgroundColor="rgba(0, 0, 0, 0.5)",
            ~paddingVertical=5.->dp,
            ~paddingHorizontal=12.->dp,
            (),
          ),
      })
    );

  [@react.component]
  let make = (~item, ~onSelectMeal) =>
    <View style=styles##mealItem>
      <TouchableOpacity onPress=onSelectMeal>
        <View>
          <View
            style={StyleSheet.flatten([|
              styles##mealRow,
              styles##mealHeader,
            |])}>
            <ImageBackground
              source={
                Image.uriSource(~uri=item.imageUrl, ())
                ->Image.Source.fromUriSource
              }
              style=styles##bgImage>
              <View style=styles##titleContainer>
                <Text style=styles##title numberOfLines=1>
                  item.title->React.string
                </Text>
              </View>
            </ImageBackground>
          </View>
          <View
            style={StyleSheet.flatten([|
              styles##mealRow,
              styles##mealDetail,
            |])}>
            <Text>
              {(item.duration->string_of_int ++ "m")->React.string}
            </Text>
            <Text>
              {item.complexity->complexityToJs->String.uppercase->React.string}
            </Text>
            <Text>
              {item.affordability
               ->affordabilityToJs
               ->String.uppercase
               ->React.string}
            </Text>
          </View>
        </View>
      </TouchableOpacity>
    </View>;
};

module CustomHeaderButton = {
  [@react.component]
  let make = () =>
    <ReasonReactNativeHeaderButtons.HeaderButton
      _IconComponent=Icons.AntDesign.make
      iconSize=23.
      color="white"
    />;
};