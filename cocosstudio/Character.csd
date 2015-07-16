<GameProjectFile>
  <PropertyGroup Type="Node" Name="Character" ID="a58d6a62-cfa3-442f-8b50-e485becd7713" Version="2.3.0.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="50" Speed="1.0000">
        <Timeline ActionTag="-990567327" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="31" Tween="False" Value="False" />
          <BoolFrame FrameIndex="50" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-616467882" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="31" Tween="False" Value="True" />
          <BoolFrame FrameIndex="50" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-49954808" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="31" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1341341742" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="31" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Ten" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="127" G="255" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="Ken" StartIndex="31" EndIndex="50">
          <RenderColor A="150" R="221" G="160" B="221" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="10" ctype="GameNodeObjectData">
        <Size />
        <Children>
          <AbstractNodeData Name="CharacterShadow" ActionTag="-1607379718" Tag="73" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-106.5000" RightMargin="-106.5000" TopMargin="-229.0000" ctype="SpriteObjectData">
            <Size X="213.0000" Y="229.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="CharacterShadow.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Ten" ActionTag="-990567327" Tag="65" IconVisible="True" TopMargin="-50.0000" BottomMargin="50.0000" ctype="ParticleObjectData">
            <Size />
            <AnchorPoint />
            <Position Y="50.0000" />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="ten.plist" Plist="" />
            <BlendFunc Src="770" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="Ken" ActionTag="-616467882" Tag="66" VisibleForFrame="False" IconVisible="True" TopMargin="-100.0000" BottomMargin="100.0000" ctype="ParticleObjectData">
            <Size />
            <AnchorPoint />
            <Position Y="100.0000" />
            <Scale ScaleX="0.2000" ScaleY="0.2000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="ten.plist" Plist="" />
            <BlendFunc Src="770" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="TenCyduck" ActionTag="-49954808" Tag="11" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-50.0000" RightMargin="-50.0000" TopMargin="-111.0000" ctype="SpriteObjectData">
            <Size X="100.0000" Y="111.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="54.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="KenCyduck" ActionTag="1341341742" Tag="67" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-50.5000" RightMargin="-50.5000" TopMargin="-114.0000" ctype="SpriteObjectData">
            <Size X="101.0000" Y="114.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="Ken.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>