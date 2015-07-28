<GameProjectFile>
  <PropertyGroup Type="Node" Name="TimingPerfect" ID="4cbb1349-8fb5-4689-868a-36cdc4ef384f" Version="2.3.1.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="playPerfect">
        <Timeline ActionTag="-909308877" Property="Scale">
          <ScaleFrame FrameIndex="1" X="2.0000" Y="2.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-909308877" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="19" Tween="False" Value="True" />
          <BoolFrame FrameIndex="20" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="playPerfect" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="0" G="191" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="959" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="perfect_1" ActionTag="-909308877" Tag="960" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-76.0000" RightMargin="-76.0000" TopMargin="-14.0000" BottomMargin="-14.0000" ctype="SpriteObjectData">
            <Size X="152.0000" Y="28.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Images/resources-1x/perfect.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>