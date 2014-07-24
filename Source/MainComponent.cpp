/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    addAndMakeVisible (sliderMin = new Slider ("new slider"));
    sliderMin->setRange (0, 100, 0);
    sliderMin->setSliderStyle (Slider::LinearHorizontal);
    sliderMin->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderMin->addListener (this);

    addAndMakeVisible (sliderMax = new Slider ("new slider"));
    sliderMax->setRange (0, 100, 0);
    sliderMax->setSliderStyle (Slider::LinearHorizontal);
    sliderMax->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderMax->addListener (this);

    addAndMakeVisible (labelMin = new Label ("new label",
                                             TRANS("min:")));
    labelMin->setFont (Font (15.00f, Font::plain));
    labelMin->setJustificationType (Justification::centredRight);
    labelMin->setEditable (false, false, false);
    labelMin->setColour (TextEditor::textColourId, Colours::black);
    labelMin->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelMax = new Label ("new label",
                                             TRANS("max:")));
    labelMax->setFont (Font (15.00f, Font::plain));
    labelMax->setJustificationType (Justification::centredRight);
    labelMax->setEditable (false, false, false);
    labelMax->setColour (TextEditor::textColourId, Colours::black);
    labelMax->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelTitle = new Label ("new label",
                                               TRANS("M+M Random Number Service")));
    labelTitle->setFont (Font (22.00f, Font::plain));
    labelTitle->setJustificationType (Justification::centred);
    labelTitle->setEditable (false, false, false);
    labelTitle->setColour (TextEditor::textColourId, Colours::black);
    labelTitle->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textEditorStatus = new TextEditor ("new text editor"));
    textEditorStatus->setMultiLine (true);
    textEditorStatus->setReturnKeyStartsNewLine (true);
    textEditorStatus->setReadOnly (true);
    textEditorStatus->setScrollbarsShown (true);
    textEditorStatus->setCaretVisible (false);
    textEditorStatus->setPopupMenuEnabled (true);
    textEditorStatus->setText (String::empty);

    addAndMakeVisible (labelStatus = new Label ("new label",
                                                TRANS("status:")));
    labelStatus->setFont (Font (15.00f, Font::plain));
    labelStatus->setJustificationType (Justification::centredRight);
    labelStatus->setEditable (false, false, false);
    labelStatus->setColour (TextEditor::textColourId, Colours::black);
    labelStatus->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButtonStart = new TextButton ("new button"));
    textButtonStart->setButtonText (TRANS("Start Service"));
    textButtonStart->addListener (this);

    addAndMakeVisible (textButtonStop = new TextButton ("new button"));
    textButtonStop->setButtonText (TRANS("Stop Service"));
    textButtonStop->addListener (this);


    //[UserPreSize]
	textEditorStatus->setText("Set Min and Max Values, then hit Start!");
	minVal = 0.0;
	maxVal = 100.0;
	sliderMin->setValue(minVal);
	sliderMax->setValue(maxVal);
    //[/UserPreSize]

    setSize (500, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderMin = nullptr;
    sliderMax = nullptr;
    labelMin = nullptr;
    labelMax = nullptr;
    labelTitle = nullptr;
    textEditorStatus = nullptr;
    labelStatus = nullptr;
    textButtonStart = nullptr;
    textButtonStop = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    sliderMin->setBounds (136, 56, 224, 24);
    sliderMax->setBounds (136, 96, 224, 24);
    labelMin->setBounds (64, 56, 64, 24);
    labelMax->setBounds (80, 96, 48, 24);
    labelTitle->setBounds (56, 8, 368, 40);
    textEditorStatus->setBounds (136, 144, 216, 224);
    labelStatus->setBounds (64, 144, 64, 24);
    textButtonStart->setBounds (96, 408, 112, 24);
    textButtonStop->setBounds (248, 408, 112, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderMin)
    {
        //[UserSliderCode_sliderMin] -- add your slider handling code here..
		minVal = sliderMin->getValue();
		if (minVal>=maxVal) //adjust max val if necessary
		{
			maxVal = minVal;
			sliderMax->setValue(maxVal);
		}
        //[/UserSliderCode_sliderMin]
    }
    else if (sliderThatWasMoved == sliderMax)
    {
        //[UserSliderCode_sliderMax] -- add your slider handling code here..
		maxVal = sliderMax->getValue();
		if (minVal>=maxVal) //adjust min val if necessary
		{
			minVal = maxVal;
			sliderMin->setValue(minVal);
		}
        //[/UserSliderCode_sliderMax]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButtonStart)
    {
        //[UserButtonCode_textButtonStart] -- add your button handler code here..
		//start the service!
		textEditorStatus->setText("starting service...");
		serviceThread = new RandomNumberServiceThread();
		serviceThread->startThread();

        //[/UserButtonCode_textButtonStart]
    }
    else if (buttonThatWasClicked == textButtonStop)
    {
        //[UserButtonCode_textButtonStop] -- add your button handler code here..
		if (serviceThread != NULL)
		{
			juce::String output = "stopping service...";
			textEditorStatus->setText(output);
			serviceThread->stopThread(2000);
			output+= "\nService stopped!";
			textEditorStatus->setText(output);
		}
        //[/UserButtonCode_textButtonStop]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="500" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="new slider" id="231d95c718db8ccf" memberName="sliderMin"
          virtualName="" explicitFocusOrder="0" pos="136 56 224 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="4ba480df3afe5d2d" memberName="sliderMax"
          virtualName="" explicitFocusOrder="0" pos="136 96 224 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="db68464994cc1855" memberName="labelMin"
         virtualName="" explicitFocusOrder="0" pos="64 56 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="min:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="3fc5fbc8b0c66691" memberName="labelMax"
         virtualName="" explicitFocusOrder="0" pos="80 96 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="max:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="184677e57ea052cf" memberName="labelTitle"
         virtualName="" explicitFocusOrder="0" pos="56 8 368 40" edTextCol="ff000000"
         edBkgCol="0" labelText="M+M Random Number Service" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="new text editor" id="980ec3016994625b" memberName="textEditorStatus"
              virtualName="" explicitFocusOrder="0" pos="136 144 216 224" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <LABEL name="new label" id="402b2e697fded5c" memberName="labelStatus"
         virtualName="" explicitFocusOrder="0" pos="64 144 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="status:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="new button" id="6b4a6fc27c843514" memberName="textButtonStart"
              virtualName="" explicitFocusOrder="0" pos="96 408 112 24" buttonText="Start Service"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="8c6ac4e089e43d06" memberName="textButtonStop"
              virtualName="" explicitFocusOrder="0" pos="248 408 112 24" buttonText="Stop Service"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
