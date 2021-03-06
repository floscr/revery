open Revery;
open Revery.UI;
open Revery.Core;

let init = app => {
  let monitor = Monitor.getPrimaryMonitor() |> Monitor.getSize;
  let width = monitor.width * 80 / 100;
  let centerX = monitor.width / 2 - width / 2;
  let height = monitor.height - 100;

  let w =
    App.createWindow(
      app,
      "flexbox-example",
      ~createOptions={...Window.defaultCreateOptions, width, height},
    );

  Window.setPos(w, centerX, 0);

  let parentWidth = width - 5;
  let childWidth = width - 50;

  let parentStyles =
      (
        ~alignment=LayoutTypes.AlignAuto,
        ~direction=LayoutTypes.Row,
        ~justify=LayoutTypes.JustifyCenter,
        (),
      ) =>
    Style.make(
      ~backgroundColor=Colors.green,
      ~position=LayoutTypes.Relative,
      ~width=parentWidth,
      ~height=100,
      ~alignItems=alignment,
      ~justifyContent=justify,
      ~flexDirection=direction,
      (),
    );

  let childStyles =
    Style.make(
      ~backgroundColor=Colors.blue,
      ~position=LayoutTypes.Relative,
      ~width=childWidth,
      ~height=40,
      (),
    );

  let defaultTextStyles =
    Style.make(
      ~fontSize=20,
      ~fontFamily="Roboto-Regular.ttf",
      ~color=Colors.white,
      ~backgroundColor=Colors.blue,
      (),
    );

  let parentColumnStyle = parentStyles(~direction=LayoutTypes.Column);
  let headerStyle =
    Style.make(
      ~marginTop=25,
      ~marginBottom=25,
      ~fontSize=30,
      ~fontFamily="Roboto-Regular.ttf",
      ~color=Colors.white,
      (),
    );

  let horizontalStyles =
    <view>
      <text style=headerStyle> "Flex Direction Row" </text>
      <view style={parentColumnStyle(~alignment=LayoutTypes.AlignAuto, ())}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Default Flex" </text>
        </view>
      </view>
      <view style={parentColumnStyle(~alignment=LayoutTypes.AlignCenter, ())}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Center" </text>
        </view>
      </view>
      <view
        style={parentColumnStyle(~alignment=LayoutTypes.AlignFlexStart, ())}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Flex Start" </text>
        </view>
      </view>
      <view
        style={parentColumnStyle(~alignment=LayoutTypes.AlignFlexEnd, ())}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Flex End" </text>
        </view>
      </view>
      <view
        style={parentColumnStyle(~alignment=LayoutTypes.AlignStretch, ())}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Flex Stretch" </text>
        </view>
      </view>
    </view>;

  let verticalStyles =
    <view>
      <text style=headerStyle> "Flex Direction Column" </text>
      <view
        style={parentStyles(
          ~direction=LayoutTypes.Column,
          ~justify=LayoutTypes.JustifyFlexStart,
          (),
        )}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Align Flex Start" </text>
        </view>
      </view>
      <view
        style={parentStyles(
          ~direction=LayoutTypes.Column,
          ~justify=LayoutTypes.JustifyCenter,
          (),
        )}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Align Flex Center" </text>
        </view>
      </view>
      <view
        style={parentStyles(
          ~direction=LayoutTypes.Column,
          ~justify=LayoutTypes.JustifyFlexEnd,
          (),
        )}>
        <view style=childStyles>
          <text style=defaultTextStyles> "Align Flex End" </text>
        </view>
      </view>
    </view>;

  let render = () => <view> horizontalStyles verticalStyles </view>;

  UI.start(w, render);
};

App.start(init);
