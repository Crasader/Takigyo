<GameProjectFile>
  <PropertyGroup Type="Node" Name="Timing" ID="58605125-ef50-47a8-b4f0-601d03b9a7a1" Version="2.3.0.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="61" Speed="1.0000" ActivedAnimationName="good">
        <Timeline ActionTag="760211662" Property="Scale">
          <ScaleFrame FrameIndex="1" X="2.0000" Y="2.0000">
            <EasingData Type="29" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="760211662" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
          <BoolFrame FrameIndex="21" Tween="False" Value="False" />
          <BoolFrame FrameIndex="61" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="760211662" Property="Alpha">
          <IntFrame FrameIndex="1" Value="204">
            <EasingData Type="29" />
          </IntFrame>
          <IntFrame FrameIndex="20" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-749525134" Property="Position">
          <PointFrame FrameIndex="61" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-749525134" Property="Scale">
          <ScaleFrame FrameIndex="21" X="2.0000" Y="2.0000">
            <EasingData Type="29" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-749525134" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="21" Tween="False" Value="True" />
          <BoolFrame FrameIndex="41" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-1167962030" Property="Position">
          <PointFrame FrameIndex="61" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1167962030" Property="Scale">
          <ScaleFrame FrameIndex="41" X="2.0000" Y="2.0000">
            <EasingData Type="29" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1167962030" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="41" Tween="False" Value="True" />
          <BoolFrame FrameIndex="61" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="perfect" StartIndex="1" EndIndex="20">
          <RenderColor A="150" R="240" G="248" B="255" />
        </AnimationInfo>
        <AnimationInfo Name="great" StartIndex="21" EndIndex="40">
          <RenderColor A="150" R="0" G="206" B="209" />
        </AnimationInfo>
        <AnimationInfo Name="good" StartIndex="41" EndIndex="60">
          <RenderColor A="150" R="47" G="79" B="79" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="296" ctype="GameNodeObjectData">
        <Size />
        <Children>
          <AbstractNodeData Name="perfect" ActionTag="760211662" Tag="297" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-76.0000" RightMargin="-76.0000" TopMargin="-14.0000" BottomMargin="-14.0000" ctype="SpriteObjectData">
            <Size X="152.0000" Y="28.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="Images/resources-1x/perfect.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="great" ActionTag="-749525134" Tag="370" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-55.5000" RightMargin="-55.5000" TopMargin="-15.5000" BottomMargin="-15.5000" ctype="SpriteObjectData">
            <Size X="111.0000" Y="31.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="great.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="good" ActionTag="-1167962030" Tag="369" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-43.5000" RightMargin="-43.5000" TopMargin="-14.5000" BottomMargin="-14.5000" ctype="SpriteObjectData">
            <Size X="87.0000" Y="29.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="good.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>