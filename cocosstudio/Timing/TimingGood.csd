<GameProjectFile>
  <PropertyGroup Type="Node" Name="TimingGood" ID="23d4415a-4dcd-4cab-aa3b-b44216ea0592" Version="2.3.1.2" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="playGood">
        <Timeline ActionTag="1389860647" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="20" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1389860647" Property="Scale">
          <ScaleFrame FrameIndex="1" X="2.0000" Y="2.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1389860647" Property="Position">
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="120.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="playGood" StartIndex="0" EndIndex="21">
          <RenderColor A="255" R="255" G="127" B="80" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="962" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="good_1" ActionTag="1389860647" Tag="963" IconVisible="False" LeftMargin="-43.5000" RightMargin="-43.5000" TopMargin="-14.5000" BottomMargin="-14.5000" ctype="SpriteObjectData">
            <Size X="87.0000" Y="29.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="2.0000" ScaleY="2.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Images/resources-1x/good.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>