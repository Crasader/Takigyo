<GameProjectFile>
  <PropertyGroup Type="Node" Name="Combo" ID="9590300d-3a0a-45de-9c5e-33898abef2c5" Version="2.3.1.2" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="339" Speed="1.0000" ActivedAnimationName="combo">
        <Timeline ActionTag="1575042069" Property="Position">
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="29" X="0.0000" Y="150.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="339" X="185.6000" Y="336.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1575042069" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="29" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1575042069" Property="Alpha">
          <IntFrame FrameIndex="1" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="29" Value="0">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="339" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="combo" StartIndex="0" EndIndex="30">
          <RenderColor A="150" R="255" G="127" B="80" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="685" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="comboLabel" ActionTag="1575042069" Tag="698" VisibleForFrame="False" Alpha="0" IconVisible="False" LeftMargin="-21.5000" RightMargin="-21.5000" TopMargin="-196.5000" BottomMargin="103.5000" FontSize="72" LabelText="0" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" OutlineSize="5" OutlineEnabled="True" ShadowOffsetX="0.0000" ShadowOffsetY="0.0000" ShadowEnabled="True" ctype="TextObjectData">
            <Size X="43.0000" Y="93.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="150.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0672" Y="0.0969" />
            <FontResource Type="Normal" Path="Fonts/Game of Three.ttf" Plist="" />
            <OutlineColor A="255" R="0" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>