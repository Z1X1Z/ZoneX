#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "StartMenu.h"
#include "radial_eq.h"
#include <iostream>
class MainContentComponent   : public Component, Timer, KeyListener
{
    
public:
    
    bool     keyStateChanged (bool isKeyDown, Component *originatingComponent) override
    {
        return true;
    }
    
    bool keyPressed (const KeyPress &key, Component *originatingComponent) override
    {
        
        if(key == KeyPress::escapeKey)
        {
            level = radial_eq->level;
            radial_eq = 0;
            
            startMenu.setVisible(true);
            startMenu.playing = false;
            startMenu.playingV = false;
        }
        /*        wchar_t * keyDown =  key.getTextCharacter();
         if(keyDown == String("=").toWideCharPointer () )radial_eq->sensitivity *= 2.f;
         if(keyDown == String("-").toWideCharPointer () )radial_eq.sensitivity *= .5f;*/
        return true;
    }
    
    
    MainContentComponent()
    {
        
        setWantsKeyboardFocus(true);
        addKeyListener(this);
        addAndMakeVisible (startMenu);
        Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
        int x = r.getWidth();
        int y = r.getHeight();
        setSize (x, y);
        Timer::startTimer(15);
    }
    
    ~MainContentComponent()
    {
        Desktop::setScreenSaverEnabled(true);
        
        removeAllChildren();
    }
    bool token = true;
    bool token2 = true;
    float incr = .5;
    bool back = false;
    int level = 1;
    ScopedPointer<Radial_eq> radial_eq;
    void timerCallback() override
    {
        if (radial_eq!=0) if (radial_eq->back) back = true;
        //  if (radial_eq==0) Time::waitForMillisecondCounter((radial_eq->time+2500)%1000);
        if (back)           {
            sleep = true;
            level = radial_eq->level;
            radial_eq=0;
            startMenu.setVisible(true);
            startMenu.playing = false;
            startMenu.playingV = false;
            back = false;
        }
   

        if (startMenu.playing)
        {   if(             radial_eq == 0)
        {
            radial_eq = new Radial_eq;
            radial_eq->level =level;
        }
            addChildComponent (radial_eq);
            if (radial_eq != 0)radial_eq->setBounds (0, 0, getWidth(), getHeight());
            
            radial_eq->engineNoiseOn = false;
            radial_eq->openGLOn = true;
            radial_eq->pulsingColorsOn = true;
            startMenu.setVisible(false);
            token = false;
            radial_eq->setVisible(true);
            if (!startMenu.playingV) radial_eq->playingV = false;
            else radial_eq->playingV = true;
            
            
        }
        else if (true)
        { int time = Time::getMillisecondCounter();
            Time::waitForMillisecondCounter((time+2500)%1000);}
        Timer::startTimer(1000);
        
        
    }
    String tips [1] ={
        "A soothing tongue is a tree of life...\nProverbs 15:4a\nThe Holy Bible"    };
    bool sleep =false;
    void paint (Graphics& g) override
    {
        if (!sleep)
        {
            g.fillAll(Colours::white);
            g.setFont(22);
        
                g.drawMultiLineText     (tips[0],getWidth()*8.5f/30.f, getHeight()/5*4.f, getWidth()*2.f/3.f)     ;
        }
        else ;
    }
    void resized() override
    {
        startMenu.setBounds (0, 0, getWidth(), getHeight());
        if (radial_eq != 0)radial_eq->setBounds (0, 0, getWidth(), getHeight());
        
    }
    StartMenu startMenu;
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
