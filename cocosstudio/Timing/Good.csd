<GameProjectFile>
  <PropertyGroup Type="Node" Name="Good" ID="aff4bf89-108b-42e8-bf96-97cdb5703280" Version="2.3.1.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="good">
        <Timeline ActionTag="-894409750" Property="Scale">
          <ScaleFrame FrameIndex="1" X="2.0000" Y="2.0000">
            <EasingData Type="29" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="19" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-894409750" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="20" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="good" StartIndex="1" EndIndex="20">
          <RenderColor A="255" R="255" G="250" B="205" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="76" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="good" ActionTag="-894409750" Tag="77" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-43.5000" RightMargin="-43.5000" TopMargin="-14.5000" BottomMargin="-14.5000" ctype="SpriteObjectData">
            <Size X="87.0000" Y="29.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
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