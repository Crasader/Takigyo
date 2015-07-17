<GameProjectFile>
  <PropertyGroup Type="Scene" Name="MainScene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="2.3.0.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="260" Speed="1.0000">
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
          <BoolFrame FrameIndex="150" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-1086158147" Property="Alpha">
          <IntFrame FrameIndex="20" Value="128">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="30" Value="255">
            <EasingData Type="25" />
          </IntFrame>
        </Timeline>
        <Timeline ActionTag="-1033247390" Property="Position">
          <PointFrame FrameIndex="60" X="320.0000" Y="-240.0000">
            <EasingData Type="29" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="320.0000" Y="9.6000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1033247390" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="60" Tween="False" Value="True" />
          <BoolFrame FrameIndex="150" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="1381406420" Property="Position">
          <PointFrame FrameIndex="60" X="25.6000" Y="-240.0000">
            <EasingData Type="29" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="25.6000" Y="9.6000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1381406420" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="60" Tween="False" Value="True" />
          <BoolFrame FrameIndex="150" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="-1578834475" Property="Position">
          <PointFrame FrameIndex="60" X="614.4000" Y="-240.0000">
            <EasingData Type="29" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="614.4000" Y="9.6000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1578834475" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="60" Tween="False" Value="True" />
          <BoolFrame FrameIndex="150" Tween="False" Value="False" />
        </Timeline>
        <Timeline ActionTag="60709847" Property="Position">
          <PointFrame FrameIndex="151" X="320.0000" Y="-144.0000">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="170" X="320.0000" Y="96.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="60709847" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="150" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="593341563" Property="Position">
          <PointFrame FrameIndex="150" X="320.0000" Y="1151.9999">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="151" X="320.0000" Y="1151.9999">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="170" X="320.0000" Y="480.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="210" X="320.0000" Y="480.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="250" X="320.0000" Y="-192.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="593341563" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="False" />
          <BoolFrame FrameIndex="150" Tween="False" Value="True" />
          <BoolFrame FrameIndex="210" Tween="False" Value="True" />
          <BoolFrame FrameIndex="260" Tween="False" Value="False" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="title" StartIndex="1" EndIndex="140">
          <RenderColor A="255" R="255" G="240" B="245" />
        </AnimationInfo>
        <AnimationInfo Name="ready" StartIndex="151" EndIndex="170">
          <RenderColor A="255" R="250" G="240" B="230" />
        </AnimationInfo>
        <AnimationInfo Name="countDown" StartIndex="210" EndIndex="260">
          <RenderColor A="255" R="255" G="69" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="background" ActionTag="-1880258662" Tag="3" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-64.0000" RightMargin="-64.0000" TopMargin="-88.0000" BottomMargin="-88.0000" ctype="SpriteObjectData">
            <Size X="768.0000" Y="1136.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.0000" Y="480.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.1882" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.5000" Y="0.5917" />
            <FileData Type="Normal" Path="sky.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="waterfall" ActionTag="-1039371130" Tag="42" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-64.0003" RightMargin="-63.9997" TopMargin="96.0000" BottomMargin="-38.0000" ctype="SpriteObjectData">
            <Size X="768.0000" Y="902.0000" />
            <Children>
              <AbstractNodeData Name="shibuki" ActionTag="-10252958" Tag="41" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="384.0000" RightMargin="384.0000" BottomMargin="902.0000" ctype="ParticleObjectData">
                <Size />
                <AnchorPoint />
                <Position X="384.0000" Y="902.0000" />
                <Scale ScaleX="3.3500" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="1.0000" />
                <PreSize />
                <FileData Type="Normal" Path="shibuki.plist" Plist="" />
                <BlendFunc Src="770" Dst="1" />
              </AbstractNodeData>
              <AbstractNodeData Name="bottomRock" ActionTag="1614960746" Tag="106" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="296.5000" RightMargin="296.5000" TopMargin="649.4400" BottomMargin="134.5600" ctype="SpriteObjectData">
                <Size X="175.0000" Y="118.0000" />
                <Children>
                  <AbstractNodeData Name="Character" ActionTag="-302421540" Tag="1" IconVisible="True" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="87.5000" RightMargin="87.5000" TopMargin="53.1000" BottomMargin="64.9000" InnerActionSpeed="1.0000" ctype="ProjectNodeObjectData">
                    <Size />
                    <AnchorPoint />
                    <Position X="87.5000" Y="64.9000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.5500" />
                    <PreSize />
                    <FileData Type="Normal" Path="Character.csd" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <Position X="384.0000" Y="252.5600" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2800" />
                <PreSize X="0.2734" Y="0.1229" />
                <FileData Type="Normal" Path="BottomRock.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="319.9997" Y="864.0000" />
            <Scale ScaleX="1.0000" ScaleY="0.9734" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.9000" />
            <PreSize X="1.2000" Y="0.7146" />
            <FileData Type="Normal" Path="waterfall.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="leftLeaves" ActionTag="81320276" Tag="43" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-213.6498" RightMargin="630.6498" TopMargin="-38.2399" BottomMargin="-108.7601" ctype="SpriteObjectData">
            <Size X="223.0000" Y="1107.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="-213.6498" Y="444.7399" />
            <Scale ScaleX="1.1065" ScaleY="0.6467" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="-0.3338" Y="0.4633" />
            <PreSize X="0.3484" Y="1.1531" />
            <FileData Type="Normal" Path="leftLeaves.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="rightLeaves" ActionTag="-2072031189" Tag="44" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="622.8522" RightMargin="-196.8522" TopMargin="-31.4398" BottomMargin="-124.5602" ctype="SpriteObjectData">
            <Size X="214.0000" Y="1116.0000" />
            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
            <Position X="836.8522" Y="433.4398" />
            <Scale ScaleX="1.1065" ScaleY="0.6467" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="1.3076" Y="0.4515" />
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
          <AbstractNodeData Name="PlayButton" ActionTag="-1033247390" Tag="39" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="197.0000" RightMargin="197.0000" TopMargin="1049.0000" BottomMargin="-240.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="216" Scale9Height="129" OutlineSize="0" ShadowOffsetX="0" ShadowOffsetY="0" ctype="ButtonObjectData">
            <Size X="246.0000" Y="151.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position X="320.0000" Y="-240.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="-0.2500" />
            <PreSize X="0.3844" Y="0.1573" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="PlayButtonPressed.png" Plist="" />
            <NormalFileData Type="Normal" Path="PlayButton.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="RankingButton" ActionTag="1381406420" Tag="37" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="25.6000" RightMargin="452.4000" TopMargin="1050.0000" BottomMargin="-240.0000" ctype="SpriteObjectData">
            <Size X="162.0000" Y="150.0000" />
            <AnchorPoint />
            <Position X="25.6000" Y="-240.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0400" Y="-0.2500" />
            <PreSize X="0.2531" Y="0.1563" />
            <FileData Type="Normal" Path="Ranking.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="CharactorButton" ActionTag="-1578834475" Tag="36" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="451.4000" RightMargin="25.6000" TopMargin="1049.0000" BottomMargin="-240.0000" ctype="SpriteObjectData">
            <Size X="163.0000" Y="151.0000" />
            <AnchorPoint ScaleX="1.0000" />
            <Position X="614.4000" Y="-240.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9600" Y="-0.2500" />
            <PreSize X="0.2547" Y="0.1573" />
            <FileData Type="Normal" Path="CharactorButton.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="lifeBG" ActionTag="60709847" Tag="60" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="132.0000" RightMargin="132.0000" TopMargin="1044.0000" BottomMargin="-144.0000" ctype="SpriteObjectData">
            <Size X="376.0000" Y="60.0000" />
            <Children>
              <AbstractNodeData Name="lifeBar" ActionTag="-675434661" Tag="61" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="18.8000" RightMargin="17.2000" TopMargin="14.5000" BottomMargin="14.5000" ctype="SpriteObjectData">
                <Size X="340.0000" Y="31.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="18.8000" Y="30.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0500" Y="0.5000" />
                <PreSize X="0.9043" Y="0.5167" />
                <FileData Type="Normal" Path="life.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" />
            <Position X="320.0000" Y="-144.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="-0.1500" />
            <PreSize X="0.5875" Y="0.0625" />
            <FileData Type="Normal" Path="life_bg.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="scoreLabel" ActionTag="593341563" Tag="64" VisibleForFrame="False" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="288.0000" RightMargin="288.0000" TopMargin="-254.4999" BottomMargin="1089.4999" FontSize="100" LabelText="0" OutlineSize="5" OutlineEnabled="True" ShadowOffsetX="5" ShadowOffsetY="-5" ShadowEnabled="True" ctype="TextObjectData">
            <Size X="64.0000" Y="125.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.0000" Y="1151.9999" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="1.2000" />
            <PreSize X="0.1422" Y="0.0240" />
            <FontResource Type="Normal" Path="Fonts/Game of Three.ttf" Plist="" />
            <OutlineColor A="255" R="0" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>