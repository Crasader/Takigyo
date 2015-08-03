<GameProjectFile>
  <PropertyGroup Type="Node" Name="Clouds" ID="45beea94-69d9-4d6e-be71-1efd2df1fe83" Version="2.3.1.2" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="500" Speed="1.0000" ActivedAnimationName="icloud">
        <Timeline ActionTag="611320670" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="500" X="-500.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="611320670" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="1469431230" Property="Position">
          <PointFrame FrameIndex="0" X="399.9990" Y="-60.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="100" X="219.9992" Y="-40.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="200" X="39.9994" Y="-70.5000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="300" X="-140.0004" Y="-35.6700">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="400" X="-320.0002" Y="-67.8400">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="500" X="-500.0000" Y="-50.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1469431230" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
        </Timeline>
        <Timeline ActionTag="2091380205" Property="Position">
          <PointFrame FrameIndex="0" X="500.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="500" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="2091380205" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Tween="False" Value="True" />
          <BoolFrame FrameIndex="1" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="icloud" StartIndex="1" EndIndex="500">
          <RenderColor A="150" R="47" G="79" B="79" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="169" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="cloud" ActionTag="611320670" Tag="41" IconVisible="False" LeftMargin="-51.0000" RightMargin="-49.0000" TopMargin="-31.5000" BottomMargin="-31.5000" ctype="SpriteObjectData">
            <Size X="100.0000" Y="63.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-1.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Images/resources-1x/cloud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="cloud2" ActionTag="1469431230" Tag="44" IconVisible="False" LeftMargin="348.1990" RightMargin="-448.1990" TopMargin="28.3000" BottomMargin="-91.3000" ctype="SpriteObjectData">
            <Size X="100.0000" Y="63.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="398.1990" Y="-59.8000" />
            <Scale ScaleX="1.1771" ScaleY="1.2108" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Images/resources-1x/cloud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="cloud3" ActionTag="2091380205" Tag="48" IconVisible="False" LeftMargin="449.0000" RightMargin="-549.0000" TopMargin="-31.5000" BottomMargin="-31.5000" ctype="SpriteObjectData">
            <Size X="100.0000" Y="63.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="499.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Images/resources-1x/cloud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>