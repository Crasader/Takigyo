<GameProjectFile>
  <PropertyGroup Type="Node" Name="Perfect" ID="32e67b69-1fc1-4cc7-8b1a-96a5a7421231" Version="2.3.1.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="perfect">
        <Timeline ActionTag="-1068947058" Property="Scale">
          <ScaleFrame FrameIndex="1" X="2.0000" Y="2.0000">
            <EasingData Type="29" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="19" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1068947058" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="20" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-1068947058" Property="Alpha">
          <IntFrame FrameIndex="1" Value="204">
            <EasingData Type="29" />
          </IntFrame>
          <IntFrame FrameIndex="19" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="perfect" StartIndex="1" EndIndex="20">
          <RenderColor A="255" R="245" G="245" B="220" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="81" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="perfect" ActionTag="-1068947058" Tag="82" Alpha="204" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-76.0000" RightMargin="-76.0000" TopMargin="-14.0000" BottomMargin="-14.0000" ctype="SpriteObjectData">
            <Size X="152.0000" Y="28.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="2.0000" ScaleY="2.0000" />
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