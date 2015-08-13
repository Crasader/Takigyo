<GameProjectFile>
  <PropertyGroup Type="Node" Name="LevelNode" ID="b70b88f1-649b-472f-985f-b57dd2b7d830" Version="2.3.2.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="119" Speed="1.0000" ActivedAnimationName="levelUp">
        <Timeline ActionTag="702009461" Property="Position">
          <PointFrame FrameIndex="40" X="30.0000" Y="140.4000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="543732051" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="1" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="-250.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="0.0000" Y="-250.0000">
            <EasingData Type="7" />
          </PointFrame>
          <PointFrame FrameIndex="118" X="0.0000" Y="-600.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="543732051" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="1" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="543732051" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="1" />
          </IntFrame>
          <IntFrame FrameIndex="40" Value="255">
            <EasingData Type="3" />
          </IntFrame>
          <IntFrame FrameIndex="80" Value="255">
            <EasingData Type="7" />
          </IntFrame>
          <IntFrame FrameIndex="118" Value="0">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="543732051" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="40" Tween="False" Value="True" />
          <BoolFrame FrameIndex="119" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="levelUp" StartIndex="0" EndIndex="120">
          <RenderColor A="255" R="255" G="250" B="240" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="881" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Level" ActionTag="543732051" Alpha="0" Tag="882" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-30.0000" RightMargin="-30.0000" TopMargin="-60.0000" BottomMargin="-60.0000" FontSize="80" LabelText="0" OutlineSize="4" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="60.0000" Y="120.0000" />
            <Children>
              <AbstractNodeData Name="Text" ActionTag="702009461" Tag="883" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-120.0000" RightMargin="-120.0000" TopMargin="-80.4000" BottomMargin="80.4000" FontSize="80" LabelText="LEVEL" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="300.0000" Y="120.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="30.0000" Y="140.4000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.5000" Y="1.1700" />
                <PreSize X="5.0000" Y="1.0000" />
                <FontResource Type="Normal" Path="kenpixel_blocks.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="0" G="0" B="0" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FontResource Type="Normal" Path="kenpixel_blocks.ttf" Plist="" />
            <OutlineColor A="255" R="0" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>