#ifndef STARTMENU_H_INCLUDED
#define STARTMENU_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class StartMenu   : public Component,
                               public Button::Listener
{
public:
        //==============================================================================
    bool playing = false;
    bool playingV = false;
    bool setting = false;
    std::unique_ptr<HyperlinkButton> hyperlinkButton;

    StartMenu()
        {
        addAndMakeVisible (playButton);
        playButton.setButtonText ("Game");
        
        addAndMakeVisible (visualizerButton);
        visualizerButton.setButtonText ("Visualizer");
        
        playButton.addListener (this);      
        visualizerButton.addListener (this);      

        hyperlinkButton.reset (new HyperlinkButton ("Donate",
                                                URL ("http://null")));
    addAndMakeVisible (hyperlinkButton.get());
    hyperlinkButton->setTooltip (TRANS("There's a lot going on in Zone:X, find out about it here!"));

     hyperlinkButton->setFont 	( 	50,	false	) 		;

         }

        ~StartMenu()
        {
                hyperlinkButton = nullptr;
            removeAllChildren();
        }

        void resized() override
        {
            float width = float(getWidth());
            float height = float(getHeight());
                        visualizerButton.setBounds (width*8.5f/30.f, height*2.f/30.f, width*13.f/30.f,height*8.f/30.f);

            playButton.setBounds (width*8.5f/30.f,height*10.f/30.f, width*13.f/30.f, height*8.f/30.f);
            hyperlinkButton->setBounds (width*8.5f/30.f, height*17.f/30.f, width*13.f/30.f, height*8.f/30.f);
            
        }

    void buttonClicked (Button* button) override
        {
        if (button == &playButton)
            {
            playing = true;
            }   
         else     if (button == &visualizerButton)
            {
            playing = true;
            playingV = true;
            }   
               
        }
private:
    TextButton playButton;
        TextButton visualizerButton;

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StartMenu)
};


#endif  // STARTMENU_H_INCLUDED
