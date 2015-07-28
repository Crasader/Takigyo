<GameProjectFile>
  <PropertyGroup Type="Node" Name="Great" ID="e1f5541f-a247-4cce-99c4-4b9109d482aa" Version="2.3.1.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="great">
        <Timeline ActionTag="-292705563" Property="Scale">
          <ScaleFrame FrameIndex="0" X="2.0000" Y="2.0000">
            <EasingData Type="29" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-292705563" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="20" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="great" StartIndex="1" EndIndex="20">
          <RenderColor A="255" R="245" G="255" B="250" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="79" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="great" ActionTag="-292705563" Tag="83" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-55.5000" RightMargin="-55.5000" TopMargin="-15.5000" BottomMargin="-15.5000" ctype="SpriteObjectData">
            <Size X="111.0000" Y="31.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0155" ScaleY="1.0155" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Images/resources-1x/great.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>