<GameProjectFile>
  <PropertyGroup Type="Scene" Name="MainScene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="2.3.0.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000">
        <Timeline ActionTag="-1086158147" Property="Position">
          <PointFrame FrameIndex="20" X="320.0000" Y="724.6080">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="320.0000" Y="892.8000">
            <EasingData Type="25" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="320.0000" Y="720.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1086158147" Property="Scale">
          <ScaleFrame FrameIndex="20" X="1.0000" Y="0.0100">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0000">
            <EasingData Type="25" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1086158147" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="20" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="-1086158147" Property="Alpha">
          <IntFrame FrameIndex="20" Value="128">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="30" Value="255">
            <EasingData Type="25" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="title" StartIndex="1" EndIndex="70">
          <RenderColor A="255" R="255" G="240" B="245" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="background" ActionTag="-1880258662" Tag="3" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-64.0000" RightMargin="-64.0000" TopMargin="-88.0000" BottomMargin="-88.0000" ctype="SpriteObjectData">
            <Size X="768.0000" Y="1136.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.0000" Y="480.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.5000" Y="0.5917" />
            <FileData Type="Normal" Path="background.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="waterfall" ActionTag="-1039371130" Tag="42" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-64.0000" RightMargin="-64.0000" TopMargin="220.8000" BottomMargin="53.2000" ctype="SpriteObjectData">
            <Size X="768.0000" Y="686.0000" />
            <Children>
              <AbstractNodeData Name="shibuki" ActionTag="-10252958" Tag="41" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="384.0000" RightMargin="384.0000" BottomMargin="686.0000" ctype="ParticleObjectData">
                <Size />
                <AnchorPoint />
                <Position X="384.0000" Y="686.0000" />
                <Scale ScaleX="3.3500" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="1.0000" />
                <PreSize />
                <FileData Type="Normal" Path="shibuki.plist" Plist="" />
                <BlendFunc Src="770" Dst="1" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="320.0000" Y="739.2000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.7700" />
            <PreSize X="1.2000" Y="0.7146" />
            <FileData Type="Normal" Path="waterfall.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="leftLeaves" ActionTag="81320276" Tag="43" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-67.9680" RightMargin="484.9680" TopMargin="-90.6840" BottomMargin="-56.3160" ctype="SpriteObjectData">
            <Size X="223.0000" Y="1107.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="-67.9680" Y="497.1840" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.1062" Y="0.5179" />
            <PreSize X="0.3484" Y="1.1531" />
            <FileData Type="Normal" Path="leftLeaves.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="rightLeaves" ActionTag="-2072031189" Tag="44" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="486.0959" RightMargin="-60.0959" TopMargin="-88.1760" BottomMargin="-67.8240" ctype="SpriteObjectData">
            <Size X="214.0000" Y="1116.0000" />
            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
            <Position X="700.0959" Y="490.1760" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="1.0939" Y="0.5106" />
            <PreSize X="0.3344" Y="1.1625" />
            <FileData Type="Normal" Path="rightLeaves.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="title" ActionTag="-1086158147" Tag="38" VisibleForFrame="False" Alpha="128" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="123.0000" RightMargin="123.0000" TopMargin="235.3920" BottomMargin="545.6080" ctype="SpriteObjectData">
            <Size X="394.0000" Y="179.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="320.0000" Y="724.6080" />
            <Scale ScaleX="1.0000" ScaleY="0.0100" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.7548" />
            <PreSize X="0.6156" Y="0.1865" />
            <FileData Type="Normal" Path="title.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="BottomRock" ActionTag="-332449404" Tag="8" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="232.5000" RightMargin="232.5000" TopMargin="833.8000" BottomMargin="8.2000" ctype="SpriteObjectData">
            <Size X="175.0000" Y="118.0000" />
            <Children>
              <AbstractNodeData Name="Charactor" ActionTag="-302421540" Tag="12" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="87.5000" RightMargin="87.5000" TopMargin="-35.4000" BottomMargin="153.4000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                <Size />
                <AnchorPoint />
                <Position X="87.5000" Y="153.4000" />
                <Scale ScaleX="1.6000" ScaleY="1.6000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="1.3000" />
                <PreSize />
                <FileData Type="Normal" Path="Charactor.csd" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.0000" Y="67.2000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.0700" />
            <PreSize X="0.1594" Y="0.0740" />
            <FileData Type="Normal" Path="BottomRock.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="PlayButton" ActionTag="-1033247390" Tag="39" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="197.0000" RightMargin="197.0000" TopMargin="761.0000" BottomMargin="48.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="216" Scale9Height="129" OutlineSize="0" ShadowOffsetX="0" ShadowOffsetY="0" ctype="ButtonObjectData">
            <Size X="246.0000" Y="151.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position X="320.0000" Y="48.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.0500" />
            <PreSize X="0.3844" Y="0.1573" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="PlayButtonPressed.png" Plist="" />
            <NormalFileData Type="Normal" Path="PlayButton.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="RankingButton" ActionTag="1381406420" Tag="37" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="25.6000" RightMargin="452.4000" TopMargin="762.0000" BottomMargin="48.0000" ctype="SpriteObjectData">
            <Size X="162.0000" Y="150.0000" />
            <AnchorPoint />
            <Position X="25.6000" Y="48.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0400" Y="0.0500" />
            <PreSize X="0.2531" Y="0.1563" />
            <FileData Type="Normal" Path="Ranking.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="CharactorButton" ActionTag="-1578834475" Tag="36" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="451.4000" RightMargin="25.6000" TopMargin="761.0000" BottomMargin="48.0000" ctype="SpriteObjectData">
            <Size X="163.0000" Y="151.0000" />
            <AnchorPoint ScaleX="1.0000" />
            <Position X="614.4000" Y="48.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9600" Y="0.0500" />
            <PreSize X="0.2547" Y="0.1573" />
            <FileData Type="Normal" Path="CharactorButton.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>