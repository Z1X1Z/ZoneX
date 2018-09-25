#ifndef radial_eq_H_INCLUDED
#define radial_eq_H_INCLUDED
#include "float.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include "math.h"
#include <iostream>
#include "pixelShaders.h"
#define pi 3.14159265359

using namespace std;

class Radial_eq   : public AudioAppComponent, OpenGLRenderer,
private Timer
{
public:
    // ScopedPointer<ThreadPool> pool;
    float radius;
    bool tok = false;
    float health, shield;
    int score = 0;
    int runTime = 0;
    float static_amp=0;
    float max_lowest_amp=0;
    vector<vector<float > > spectrum_raw;
    vector<vector<float > > testfrq;
    float shipScale = .3;
    vector<vector<float > > spectrum_sorted;
    
    Colour transparent =Colour(  1.f,1.f,1.f,.0f);
    bool star_on = false;
    float breakthrough_amp;
    float trailLength;
    int resolution;
    GLfloat zoom = -0.385938;
    float max_zoom = 100000.0;
    bool zoom_in = true;
    GLfloat rainbowizer = 0;
    ScopedPointer<OpenGLShaderProgram> shader;
    ScopedPointer <OpenGLGraphicsContextCustomShader> customShader;
    int frame = 0;
    GLfloat coordy;
    GLfloat coordx;
    int call_back_time = 1000;
    bool shadersOn;
    bool openGLOn;
    bool engineNoiseOn;
    bool pulsingColorsOn;
    int inum = 4;
    bool booting = false;
    bool token = false;
    bool soundOn;
    float angle;
    float d_x;
    float d_y;
    float pitch;
    double amplitude;
    int cycles = 0;
    double links;
    bool linked = false;
    float sensitivity = 1.0f;
    float spirray[10000][2];
    double notes[144]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    double numOfNotes[144]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    
    double testar[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double testarD[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double octave[120], octaveDensity[120]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
    
    float notes1000[1000], notesBuffer[1000];
    int negatizer [2] = {1,-1};
    Colour centCol;
    struct bubbles
    {
        float radii;
        float x;
        float y;
        Colour centCol;
        Colour pitchCol;
    };
    struct spiralColourStruct
    {
        Colour color;
    };
    bubbles trail [1001];
    spiralColourStruct colours[1000];
    
    float max1 = 0;
    float min1 = 10000000;
    struct soundata {float freq; float amp; float note;};
    static bool sortByNote(soundata &lhs, soundata &rhs) { return lhs.note < rhs.note; }
    float maxOct = 0;
    
    
    struct bin {
        double mag;
        double phase;
        double idealFreq;
        double freq;
    };
    
    float  maxFreq = 0;
    
    float tau(float x)
    {
        return 1/4. * log(3*pow(x,2)+ 6*x + 1) - pow(6,.5)/24 * log((x + 1 - pow(2./3 ,2))  /  (x + 1 + sqrt(2./3)));
    }
    
    float mag (dsp::Complex<float> z){ return pow(pow(z.real(),2)+pow(z.imag(),2),.5);}//
    void spiral_compress()
    {
        float freq = 0;
        maxFreq = 0;
        max1 = 0;
        min1 = 100000;
        double amp;
        double frq;
        int note;
        for(int n = 0; n<24; n++){testar[n] = 0;testarD[n] = 1;}
        
        for(int n = 0; n<120; n++){
            octave[n] = 0;
            octaveDensity[n] = 0;
        }
        
        auto z = (dsp::Complex<float>*)fftDataC;
        int maxA, maxN, outAmp =-1;
        
        for(int t=2; t<140; t+=1)//n<fftSize1/4-100
        {
            int n =t;
            //if (fftSize1/4<t) n =abs(t-int(t)/(int(fftSize1/4)));
            amp =mag(z[n]);// fftData11[2*n]; //
            if( amp>mag(z[n-1]) and amp > mag(z[n+1]) and not(isnan(mag(amp))) )
            {
                
                double    ap = (z[n + 1].real()* z[n].real() + z[n+1].imag()* z[n].imag())  /  (z[n].real()* z[n].real() + z[n].imag()* z[n].imag());
                double  dp = -ap / (1 - ap);
                double   am = (z[n - 1].real()* z[n].real() + z[n - 1].imag()* z[n].imag())  /  (z[n].real()* z[n].real() + z[n].imag()* z[n].imag());
                double   dm = am / (1 - am);
                double   d = (dp + dm) / 2 + tau(dp* dp) - tau(dm* dm);
                double nAdj = n;
                if (abs(d)<3) nAdj = n + d;
                //if (abs(nAdj-n) < 10)
                freq =double( double(double(sampleRate/10000.)*double(nAdj))/fftSize1)*10000;
                float b;
                if(amp>b) {b = amp; maxFreq = freq;}
                
                if(not(isnan(freq) or isnan(amp) or isinf(amp)) and freq != -33)
                {
                    float g = pow ( 2, (1/24.f));
                    float aa = freq/440.0;
                    float note = log(aa)/log(g)+69*2;
                    int f = 120;
                   
                    testar[int(round(note))%24] += std::abs(amp);
                    testarD[int(round(note))%24] += 1;
                }
            }
        }
        
        //below is partial duplicate of above, modified for lower fft, could be refactored
        /*
         for(int n=0; n<fftSize1 - 1;n+=2)
         {
         amp = fftData[n];
         double fr = 4.41*(n)/fftSize*10000.f;
         
         
         if (frq!=0)
         {
         
         double g = pow ( 2, (1/24.f));
         double aa = fr/440.0;
         double m = log(aa)/log(g)+69-16;
         
         if (m>=0 and octaveDensity[int(round(gent[n].n))] <1){
         octave[int(round(m))] += abs(amp);
         octaveDensity[int(round(m))] += 1;
         }
         
         }
         
         }
         */
        
        for( int n=0; n<120; n++)  octave[n] /= octaveDensity[n];
        float val;
        int no;
        //sort(begin(fftData113), end(fftData113), sortByNote);
        for(int n=0; n<24;++n) {
            //testar[n] /= testarD[n];
            double absamp = testar[n];
            
            if(absamp>max1) {max1 =absamp;}
            if(absamp<min1) min1 = absamp;
        }
        
        maxOct = 0;
        int maxNN;
        for(int n=0; n<120;n+=1) {
            if(octave[n]>maxOct ) {maxOct = octave[n]; maxNN = n;}}
        
        
        
        
    };
    
    
    
    bool backgrounded=false;
    int64 timeToSleep;
    int64 timeToLightsOut = 1000*60*8;
    struct touchPitch {float amp = 0; double framesPassed = -2; float phase=0;
        float exitAngle =0;
        float angle =2*pi;
        float angleAmp = 2*pi;
        float cumulativeAngleShift = 0;
        float enterAngle = 0;
        bool firstDrag = false;
        float freq =1 ; bool pitchJustOff=false;   bool soundJustStarted = true;
        bool pitchOn = false;
       bool pitchChanged = false;};
   touchPitch touchPitches[10];


float pressAmp = 0;
    float shift = -1.25;
    virtual void 	mouseDown (    const MouseEvent &event)override{
        touchPitch t =touchPitches[event.source.getIndex()];
        if(t.framesPassed < -1 or t.framesPassed > sampleRate) {t.framesPassed = sampleRate;
        }
        if(!t.soundJustStarted and !t.pitchOn and !t.pitchJustOff){t.angleAmp =0; t.cumulativeAngleShift = 0;

        }
       t.soundJustStarted = true;
        t.pitchJustOff = false;
        t.pitchOn = true;
        backgrounded = false;
        sleep = false;
    timeToSleep = Time::currentTimeMillis()+timeToLightsOut;
        touchPitches[event.source.getIndex()] =t;
        touchPitches[event.source.getIndex()].angle
        = getTouchPitch(event);
        if (!sleep and t.framesPassed == 0) {
            touchPitches[event.source.getIndex()].angleAmp = touchPitches[event.source.getIndex()].cumulativeAngleShift = 0;
            touchPitches[event.source.getIndex()].enterAngle = 0;

            touchPitches[event.source.getIndex()].exitAngle = 0;
    
        }
       
        if(touchPitches[event.source.getIndex()].angle<0)touchPitches[event.source.getIndex()].angle
                                                                 =touchPitches[event.source.getIndex()].angle+2*pi;
        else if (touchPitches[event.source.getIndex()].angle>2*pi)touchPitches[event.source.getIndex()].angle
                                                                          =touchPitches[event.source.getIndex()].angle-2*pi;

     if(!sleep)getTouchPitch(event);

    }
    float getTouchPitch(  const MouseEvent &event){
     
        
        float angle1;

        float x = event.getPosition().getX()-getWidth()/2.;

        float y = event.getPosition().getY()-getHeight()/2.;
        angle1 = atan2(y,x);
        float angle2 = angle1;
        angle2+= 4*pi;
        angle2 += pi/2;

        touchPitches[event.source.getIndex()].cumulativeAngleShift += 4*pi;
       // DBG(  touchPitches[event.source.getIndex()].cumulativeAngleShift);
        touchPitches[event.source.getIndex()].cumulativeAngleShift=
              touchPitches[event.source.getIndex()].cumulativeAngleShift-
                       int(abs(touchPitches[event.source.getIndex()].cumulativeAngleShift)/(2*pi))*2*pi;
        
        
        angle2=    angle2-int(abs((angle2-  touchPitches[event.source.getIndex()].cumulativeAngleShift))/(2*pi))*2*pi;
            touchPitches[event.source.getIndex()].freq  = pow (2,(
            (angle2)
            /pi/2*12+shift)/12.)*440
            ;
        
        touchPitches[event.source.getIndex()].angleAmp = touchPitches[event.source.getIndex()].cumulativeAngleShift;
     DBG(touchPitches[event.source.getIndex()].freq);

        DBG(touchPitches[event.source.getIndex()].angleAmp);

        return  angle1;
    }
   virtual void  mouseDrag (const MouseEvent &event) override{
       
     touchPitches[event.source.getIndex()]. pitchChanged = true;
       
      if(!(touchPitches[event.source.getIndex()].exitAngle==0)) touchPitches[event.source.getIndex()].cumulativeAngleShift +=
       -(touchPitches[event.source.getIndex()].exitAngle)+
       (touchPitches[event.source.getIndex()].enterAngle);


       touchPitches[event.source.getIndex()].exitAngle = touchPitches[event.source.getIndex()].enterAngle;

       
       
       touchPitches[event.source.getIndex()].enterAngle = touchPitches[event.source.getIndex()].angle
       = getTouchPitch(event);
       
       

}
virtual void 	mouseUp (    const MouseEvent &event)override{
    touchPitches[event.source.getIndex()].exitAngle = touchPitches[event.source.getIndex()].enterAngle=0;
    touchPitch t = touchPitches[event.source.getIndex()];
    t.pitchOn = false;
    t.pitchJustOff = true;
    t.soundJustStarted = false;
    touchPitches[event.source.getIndex()] =t ;

}

    /*
    virtual void     suspended ()
    {//backgrounded = true;
        
    //suspendProcessing (true);
}
    virtual void     resumed (){//backgrounded = false;    
           // suspendProcessing (false);

                                         setAudioChannels (1, 1);
                                         auto* device = deviceManager.getCurrentAudioDevice();
                                         AudioDeviceManager::AudioDeviceSetup audioDeviceSetup;
                                         deviceManager.getAudioDeviceSetup(audioDeviceSetup);
                                         sampleRate = audioDeviceSetup.sampleRate;
                                         startTimer(callbackWait);
    }
    
    */
    
    void newOpenGLContextCreated () override
    {
       // customShader = new OpenGLGraphicsContextCustomShader(fragmentShaderString);
    }
    
    float on = 1.0f;
    bool tik = false;
    void renderOpenGL() override
    {

        GLfloat height = resy;
        GLfloat width = resx;
        
        if (!tik) { jassert (OpenGLHelpers::isContextActive()); tik = true;}
        if (zoom < max_zoom and zoom_in) zoom += zoom/100;
        else if(zoom >.2)
        {
            zoom_in = false;
            zoom -= zoom/3.;
        }
        else zoom_in = true;
        //if (pulsingColorsOn)
        //rainbowizer += .002;
        if (linked)
        {
            shader->use();
            shader->setUniform("on", on);
            
            shader->setUniform("coordy", coordy);
            shader->setUniform("coordx", coordx);
            shader->setUniform("zoom", zoom);
            shader->setUniform("rainbowizer", rainbowizer);
            shader->setUniform("height", height);
            shader->setUniform("width", width);
            
        }
    }
    
    void openGLContextClosing() override
    {
        shader.release();
        shader = nullptr;
        customShader = nullptr;
        
    }
    int passes = 0;
    
    int cleaning()
    
    {
        for(int pass = 0; pass <    20; pass++)
        {
            break;
            
        }
        
        
        return 1;
    }
    float max_amp=0;
    int moving;
    int movingSpeed = 30;
    bool shrinking;
                 float minCoord = 1000000;

    void move()
    {
        float magnitude;
        float volumeModifier = pow(10,100*maxFrame)/pow(10,100*lastMaxFrame);
        if( volumeModifier < 1)volumeModifier=1;
                if( volumeModifier > 3)volumeModifier=3;
        if (pitch>0)
            magnitude =2500*15/minCoord*shipScale*android*volumeModifier;//*(max1+.2);
                 
        else magnitude = 0;
      
        //if (magnitude >40*500/maxCoord) magnitude = 80*500/maxCoord;
   
        radius = magnitude*3;
        
        if (pitch>0)
        {
            shrinking = false;
            moving += 1;
            float g = pow ( 2, (1/24.0));
            float aa = pitch/440.0;
            float note = log(aa)/log(g)+49;
            float inc = 5.5;
            int t =  int(-note * 30+30*inc);
            angle = t%360;
            Colour pitchCol = Colour::fromHSV((angle-60)/360.,.7,1.f,1.);
            trail[0].pitchCol = pitchCol;
            
            d_x = -magnitude/4*-sin(angle*(2*pi)/360);
            d_y = -magnitude/4*-cos(angle*(2*pi)/360);
            coordx+=d_x*.001;
            coordy+=d_y*.001;
        }
        if(pitch==0)
        {
            shrinking = true;
            if (moving > movingSpeed) moving = movingSpeed;
            if (moving > 1) moving -= 1;
            trail[0].pitchCol = transparent;
            
            d_x = 0;
            d_y = 0;
        }
        bubbles trail_buffer[1000];
        trailLength= 17;
        for(int n = 0; n < trailLength; n++)
        {
            trail_buffer[n]=trail[n];
        }
        int interpolationFactor = timeDif/(callbackWait-1);
        if (interpolationFactor>30) interpolationFactor=30;
        else if (interpolationFactor<1) interpolationFactor=1;
        
        for(int n = 0; n<interpolationFactor;n++)
        {
            trail[n].x = d_x*n*pow(1.01,n);
            trail[n].y = d_y*n*pow(1.01,n);
            trail[n].radii = radius*pow(.967,n);
            trail[n].pitchCol = trail[0].pitchCol;
        }
        cycles=trailLength;
        
        for(int n = 0; (n -1) < trailLength; n++)
        {
            trail[n+interpolationFactor].x = (trail_buffer[n].x)*1.01+d_x*(interpolationFactor+1);
            trail[n+interpolationFactor].y = (trail_buffer[n].y)*1.01+d_y*(interpolationFactor+1);
            trail[n+interpolationFactor].radii = trail_buffer[n].radii*pow(.967,n+interpolationFactor);
            //float adjCol = trail_buffer[n].pitchCol.getAlpha()/255.f*.99f;
            trail[n+interpolationFactor].pitchCol = trail_buffer[n].pitchCol;//.withAlpha(adjCol);
        }
        for(int n = 0; n < polygons.size(); n++)
        {
            polygons[n].centerX += d_x*interpolationFactor+polygons[n].dx;
                        polygons[n].centerY += d_y*interpolationFactor+polygons[n].dy;
                       float xFromCent = (polygons[n].centerX-getWidth()/2);
                       float yFromCent = (polygons[n].centerY-getHeight()/2);
                        float dist = pow(xFromCent*xFromCent+yFromCent*yFromCent,.5);
                        if ( dist<minCoord/3)
            {
                
                        float speed = .01*(2-1./level)*interpolationFactor/minCoord*500;
                        float speedLimit = d_x*(1+level/(10+level))*.4;
                        float ddx = xFromCent*(minCoord/3-dist)/minCoord/3*speed*interpolationFactor;
                        if (polygons[n].dx+ddx<speedLimit and polygons[n].dx+ddx>-speedLimit)polygons[n].dx+=ddx;
                        float ddy =  yFromCent*(minCoord/3-dist)/minCoord/3*speed*interpolationFactor;
                        if (polygons[n].dy+ddy<speedLimit and polygons[n].dy+ddy>-speedLimit)polygons[n].dy+=ddy;
                        
            }

            if ( dist<(polyRad+minCoord/22 )and polygons[n].exited){
                if (!polygons[n].caught)polygons[n].caught = true;
                else polygons[n].caught = false;

                polygons[n].exited = false;}
                
            else if (dist>polyRad+minCoord/22)polygons[n].exited = true;
                
                
            if (xFromCent>(getWidth()/2))polygons[n].centerX = -0;
            else if (xFromCent<-(getWidth()/2))polygons[n].centerX = (getWidth());
            if (yFromCent>(getHeight()/2))polygons[n].centerY = 0;
            else if  (yFromCent<-getHeight()/2)polygons[n].centerY = (getHeight());

                        
        }
    }
    
    float averageColour[3] = {0,0,0};
    float largest_loop;
    float phase = 0.0f;
    int length = 0;
    
    void makeSpirograph()
    {
        float lastLength = length;
        length = 0;
        links= bufferSize;
        if (links > 512) links = 512 ;

        if (maxFreq > 0)while (maxFreq<500) maxFreq*=2;

        float adjConstant = 1/1.61803398875*pi*2*maxFreq/20000*44100/sampleRate;
        for(int m = 0; m < links/1.2; m++)
        {
            if (not(spiraAudio[m]==0 or isinf(spiraAudio[m]) ))
            {
                float samp = (spiraAudio[m]);
                
                phase = length*adjConstant;//spira_pitch;
                spirray[length][0]=-sin(phase)*samp;
                spirray[length][1]=-cos(phase)*samp;
                length++;
            }
        }
        length -= 1;
        largest_loop = 0;
        for(int x = 0; x<length; x++)
        {
            if (std::abs(spirray[x][0])>largest_loop)largest_loop =
                std::abs(spirray[x][0]);
            if (abs(spirray[x][1])>largest_loop)largest_loop =
                abs(spirray[x][1]);
        }
        
        
        
    }
        
    Image lode;
    float cent;
    float counter = 0;
    uint32 lastTime=-1;
    uint32 time;
    float timeDif;
    float callbackWait = 1000/60.f;
    int level = 1;//levels count down
    int polyRad;
    bool playingV = true;
    bool displayCountdown;
    bool back = false;
    void timerCallback() override
    {
        
                                       {

            #if defined JUCE_ANDROID or JUCE_IOS
        if (timeToSleep <Time::currentTimeMillis()
) back = true;//backgrounded = true;
  else if (timeToSleep <Time::currentTimeMillis() + 10000
) displayCountdown = true;
else displayCountdown = false;
                        #endif

                                
     if (playingV)     shipScale = .9;
                else shipScale = .3;

        if (getHeight()<=getWidth()) minCoord = getHeight();
        else minCoord = getWidth();
        bool allCaught = true;
        for (int n=0; n<polygons.size(); n++) if(  polygons[n].caught == false) allCaught = false;

        if(allCaught and !playingV)
        {
                        level +=1;
            polygons.clear();

            polygon pol;
            polyRad = 7*10/level*minCoord/300.;
            int sides = level+1;
        polPath.clear();
        for (int n = 0; n < sides; n ++) {
     
                
                if (n == 0) polPath.startNewSubPath( sin(2*pi/sides*n)*polyRad, cos(2*pi/sides*n)*polyRad);
                else polPath.lineTo(sin(2*pi/sides*n)*polyRad, cos(2*pi/sides*n)*polyRad);
        }
       polPath.closeSubPath();

            for(int n = 0; n<(level+1); n++){
            pol.centerX = (getWidth())/2+cos(2*pi/(level+1)*n)*(minCoord-polyRad)/2*.7;
                        pol.centerY = (getHeight())/2+sin(2*pi/(level+1)*n)*(minCoord-polyRad)/2*.7;
        
            polygons.push_back(pol);
            }
        }
                else if(playingV)            polygons.clear();


            
            if(lastTime!=-1)timeDif= time-lastTime;
            else lastTime = 1;
            if (timeDif <=16) timeDif = 16;
            lastTime = time;
            
            //while( pool->getNumJobs()>0);
            //spiral_compress3();
            if (nextFFTBlockReady)
            {
                // forwardFFT.performFrequencyOnlyForwardTransform (fftData);
                //spiral_compress2();
                nextFFTBlockReady = false;
            }
            if (nextFFTBlockReady1)
            {
                //  forwardFFT1.performRealOnlyForwardTransform (fftData1,true);
                //for (int b = 0; b<fftSize1; b ++)fftDataC[b] *= -sin(b*pi/fftSize1);
                
                float last_pitch=pitch;
                pitch =  getPitch(audioBuf);
                if (pitch == -1 and counter <2){counter +=1; pitch=last_pitch;}
                else if(pitch == -2){ pitch = last_pitch;}
                else if(pitch>0){counter = 0;pitch =pow(pitch*3322.4/3951.1,.5);}
                else pitch = 0;
                spira_pitch = pitch;
                
                forwardFFT1.performRealOnlyForwardTransform(fftDataC);
                //  for (int i = 0; i < fftSize1; ++i)
                //    fftData11[i] = fftDataC[i];
                
                //forwardFFT1.performRealOnlyForwardTransform (fftData1);
                spiral_compress();
                nextFFTBlockReady1 = false;
                
            }
            if (moving >4 and !shrinking)
            makeSpirograph();
            
            move();
            //const MessageManagerLock mmLock;
            repaint();
            
            // while(pool->getNumJobs()>0);
        }
                            startTimer(callbackWait);

    }
    float spira_pitch = 1;

    ~Radial_eq()
    
    {
        //openGLContext.detach();
        shutdownAudio();
        removeAllChildren();
    }
    
    int piano[12]={1,0,1,0,1,1,0,1,0,1,0,1};
    int resx;
    int resy;
    bool sleep = false;
    void paint (Graphics& g) override
    {
        
  
        if (backgrounded)
        {g.fillAll(Colours::black);
            g.setColour(Colours::white);
            g.setFont(100);
            g.drawMultiLineText 	("Tap\nTo\nGo",
            0, 100, getWidth())	;
        sleep = true;
        
        }
        else{
    
        runTime+=1;
        
        g.fillAll(Colours::grey);
                      if (displayCountdown){
                        g.setColour(Colours::red);
                                    g.setFont(50);

            int time = (timeToSleep -Time::currentTimeMillis())/1000;
            String warning = String("Pausing \nin: \n") ;
            warning +=String(time);
            g.drawMultiLineText 	(warning,
            
            0, 100, getWidth())	;
        }

        float wd2 =  getWidth()/2.;
        float hd2 =  getHeight()/2.;
        
        float wd =  getWidth();
        float hd =  getHeight();
        resolution = pow(2,8);
        
        /*
         if (getHeight() < resolution) resolution = getHeight();
         else if (getWidth()< resolution)resolution = getWidth();
         
         
         if (getHeight()>=getWidth())
         {
         resx = resolution*wd/hd;
         resy = resolution;
         }
         else
         {
         resx = resolution;
         resy = resolution*hd/wd;
         }
         
         if(!linked)
         {
         shader = customShader->getProgram(g.getInternalContext())  ;
         Result result = customShader->checkCompilation(g.getInternalContext());
         shader->link();
         
         linked = true;
         }
         
         Rectangle<int> b = Rectangle<int>(0,0,getWidth(),getHeight());
         customShader->fillRect(g.getInternalContext(), b);
         
         lode = Image    (     Image::RGB,        resx,        resy,        true    )     ;
         unsigned short data[4*resx*resy];
         glReadPixels(  0,    0,  resx,  resy,  GL_RGBA,  GL_UNSIGNED_SHORT, data);
         for ( int x = resx*resy*4; x>0; x-=4)
         {
         int nPix = x/4;
         lode.setPixelAt (nPix%(resx), nPix/resx, Colour(char(data[x]), char(data[x+1]), char(data[x+2]))) ;
         }
         AffineTransform scale = AffineTransform::scale (float(getWidth())/float(resx),float(getHeight())/float(resy));
         
         g.drawImageTransformed (lode, scale, false);
         
         */
        for(int n = 0; n<cycles; n++)
        {
            g.setColour (trail[cycles-n].pitchCol);
            // if (!(isnan(trail[cycles-n].x) or isinf(trail[cycles-n].x) or isnan(trail[cycles-n].y) or abs(trail[cycles-n].y-hd2)>hd2 or abs(trail[cycles-n].x-wd2)>wd2) )
            g.fillEllipse(wd2+trail[cycles-n].x-trail[cycles-n].radii/2,hd2+trail[cycles-n].y - trail[cycles-n].radii/2,trail[cycles-n].radii, trail[cycles-n].radii);
        }
        
         
        g.setColour (Colours::black);
        for (int n = 0; n<polygons.size();n++)
            {
                if (!polygons[n].caught)            g.setColour(Colours::black);
                else             g.setColour(Colours::white);


            
        int centerX = polygons[n].centerX;
         int centerY = polygons[n].centerY;
         AffineTransform affine;
        g.fillPath(polPath,affine.translated(polygons[n].centerX, polygons[n].centerY));
            
            }
        g.setColour (Colours::white);
        Path spirograph;
        int tk = getHeight();
        largest_loop *= 1;
        
        if (tk>getWidth())tk = getWidth();
        float growth = moving*1./movingSpeed;
        if (growth > 1) growth = 1;
        if (moving>4){
        
        for (int n = 0; n < length; n ++) {
            float x = spirray[n][0]/largest_loop*tk/4*growth*shipScale;
            float y =  spirray[n][1]/largest_loop*tk/4*growth*shipScale;
            
            if(not(isnan(std::abs(x)) or isnan(std::abs(y)) or abs(x)>wd2 or  abs(y)>hd2))
            {
                if (n == 0) spirograph.startNewSubPath( x+wd2, y+hd2);
                else spirograph.lineTo (x+wd2,y+hd2);
            }
            else if (n == 0)  spirograph.startNewSubPath( 0, 0);
        }
        
        g.strokePath(spirograph, PathStrokeType(1.4f*shipScale));
        }
        
        float amp;
        int incrementation = 12;
        Path star;
        Path stars[12] = {};
        for(int n=0; n<24; ++n)
        {
            bool thi = false;
            // amp = (testar[n]-min1)/(max1-min1);
            int f = 200;
            
            amp = atan(testar[(n+incrementation)%24]/max1*pi);
            amp = log(testar[(n+incrementation)%24]*f)/log(max1*f);
            amp = atan (amp/3.f)*3*shipScale;
            //amp = testar[(n+10)%24]/max1;
            float scale = amp*200;
            if (scale<.01) scale = .01;
            if (scale>200*shipScale) scale = 200*shipScale;
            float endX =wd2+ cos(pi*2*n/24) * scale ;
            float endY =hd2 + sin(pi*2*n/24)  * scale;
            
            
            
            if(thi) g.fillEllipse(endX,endY, 10,10);
            
            
            if(not(isnan(endX) or isnan(endY) or isinf(endX) or isinf (endY)))
            {
                star.startNewSubPath (wd2, hd2 );
                star.lineTo(endX, endY );
                
                Colour color = Colour::fromHSV(1-(n-2)%24/24.f    ,
                                               1.f,1.f,1.0);
                g.setColour (color);
                
                g.strokePath( star, PathStrokeType(5.f) );
                star.clear();
            }
            
        }
        
        
        g.setColour (Colours::black);
        
        g.drawText     ( String(timeDif),    Rectangle<int>(0,0,100,100),     Justification::centred    ) ;
        
        
        
        
        /*
         Path rainbowstar;
         for(int n = 0; n<24; n++)
         {
         incremented = (n)%(24)+24-24/12;
         amp = pow(notes[(incremented)%(24)]/sensitivity/30,.5);
         amp = log(amp*13);
         amp = 140 * amp;
         if (amp<.01) amp = .01;
         else if (amp >getWidth()/5) amp = getWidth()/5;
         angle = float( 3.14159 * 2 / (24)* (n+24/12));
         
         
         g.setColour (color);
         rainbowstar.startNewSubPath (wd2, hd2);
         float endX = wd2+ cos( angle )  * amp ;
         float endY = hd2 + sin( angle )  * amp;
         //    rainbowstar.lineTo(endX, endY);
         //  g.strokePath( rainbowstar, PathStrokeType (7.f));
         rainbowstar.clear();
         
         
         
         
         if(n%2 == 0)
         for(int r = 0; r<120; r+=12)
         {
         
         endX = wd2+ cos( angle +2*pi*4/12)  * 100 ;
         endY = hd2 + sin( angle +2*pi*4/12)  * 100;
         int note = n/2;co
         float octamp = (log((octave[r+note]/maxOct+1)*500)-log(500))*50;
         if (octamp > 50)octamp = 50;
         if (octamp <1)octamp = 1;
         if((isnan(octamp) or isnan(octamp) or isinf(octamp) or isinf (octamp))) octamp = 1;
         stars[note].startNewSubPath (endX, endY );
         // g.fillEllipse(endX+ cos( 2*pi/12*(x+fc%12))* octamp, endY + sin( 2*pi/12*(x+fc%12)* octamp),10,10);
         
         stars[note].lineTo(endX+ cos( 2*pi/12*((r/12+note+2)%12))* octamp, endY + sin( 2*pi/12*(r/12+note+2))* octamp);
         
         //g.drawText     ( String((n+r*12+3)%144),    tippitytip,     Justification::centred    ) ;
         }
         
         
         
         
         }
         
         
         
         
         
         
         for (int x = 0; x<12; x++)
         {
         g.setColour (Colours::yellow);
         
         if (piano [(x+16)%12] == 1)
         g.setColour (Colours::white);
         else                                            g.setColour (Colours::black);
         
         
         //g.strokePath( stars[x], PathStrokeType  (7.7f));
         }
         
         */
        }
    }
    int fps;
    int second;
    int  fftspeed = 0;
    double sampleRate = -1;
    
    void load(){
        
        
        //    pool = new ThreadPool(5);
        
         #if not JUCE_IOS
        openGLContext.setMultisamplingEnabled(false);
        openGLContext.setRenderer (this);
        openGLContext.setContinuousRepainting(false);
        openGLContext.attachTo(*this);

           #endif
        setOpaque (true);
        
        
        
        RuntimePermissions::request (
                                     RuntimePermissions::recordAudio,
                                     [this] (bool wasGranted)
                                     {
                                         if (! wasGranted)
                                         { }
                                                                                  auto* device = deviceManager.getCurrentAudioDevice();

                                          auto numOutputChannels = device != nullptr ? device->getActiveOutputChannels().countNumberOfSetBits() : 2;
                                         setAudioChannels (1, numOutputChannels);
                                         AudioDeviceManager::AudioDeviceSetup audioDeviceSetup;
                                         deviceManager.getAudioDeviceSetup(audioDeviceSetup);
                                         sampleRate = audioDeviceSetup.sampleRate;
                                         
                                     }
                                     
                                     );
        spiral_compress();
        startTimer (1);};
        int64 startTime;
        float android = 1;
    Radial_eq() :
    forwardFFT (fftOrder),
    forwardFFT1 (fftOrder1),
    forwardFFT11 (fftOrder1)
    {
        
             #if defined JUCE_ANDROID
                    android = 1/4.;
                    #endif
    timeToSleep = Time::currentTimeMillis()+timeToLightsOut;
        load();

    }
    
    
    //==============================================================================
    void prepareToPlay (int /*samplesPerBlockExpected*/, double /*newSampleRate*/) override
    {
        // (nothing to do here)
    }
    
    void releaseResources() override
    {
        // (nothing to do here)
    }
    int finalVal = 0;
    touchPitch lastTouchPitches[10];
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        if (bufferToFill.buffer->getNumChannels() > 0)
        {
            const auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
            if (!backgrounded)
            for (auto i = 0; i < bufferToFill.numSamples; ++i){

                float b = channelData[i];
                if(isnan(b))b=0;
                pushNextSampleIntoFifo(b);

            }

        }
        bufferToFill.clearActiveBufferRegion();

            for (int f = 0; f<10; f++){
            touchPitch t = touchPitches[f];
                
                float                      phaseBuffer = t.phase;
                double framesPassed = t.framesPassed;
                if (t.pitchJustOff ){t.soundJustStarted = false;}
            if (t.pitchJustOff and t.framesPassed >= sampleRate )
            {t.pitchJustOff = false;}
            if ((t.pitchOn or t.pitchJustOff) and !backgrounded) {
                float bv = (1. / sampleRate * (2 * pi * t.freq));
                // float bq =(1./sampleRate*( 2*/pi*lastTouchPitch));
                t.phase *= t.freq / lastTouchPitches[f].freq;
                        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels();
                             ++channel) {
                            phaseBuffer = t.phase;
                            float decayBuffer = 1;
                            framesPassed = t.framesPassed;
                            auto *buffer = bufferToFill.buffer->getWritePointer(channel,
                                                                                bufferToFill.startSample);
                            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {

                                phaseBuffer += bv;

                        if (t.pitchJustOff)
                            decayBuffer = 1 - 1. / (sampleRate) * (framesPassed);
                        if (t.soundJustStarted)
                            decayBuffer = 1. / (sampleRate) * (sampleRate - framesPassed);
                        if (framesPassed < sampleRate and t.pitchJustOff )
                            framesPassed += 1;
                        if (framesPassed > 0 and t.soundJustStarted )framesPassed -= 1;
                       // if (f == 0) buffer[sample] = 0;
                        buffer[sample] +=  (-sin(phaseBuffer  )*(t.angleAmp) / (2 * pi) +
                                          -sin(phaseBuffer * 2) * (2 * pi - t.angleAmp) / (2 * pi) )
                                           / 20. *decayBuffer;
                                
                    }

            }


            }

                t.phase = phaseBuffer;
                t.framesPassed =framesPassed;
                //t.pitchChanged = false;
                t.phase -= (2 * pi) * int((t.phase) / (2 * pi));
                touchPitches[f] =t;
                lastTouchPitches[f] = touchPitches[f];

            }


         if(false and backgrounded)  {
                                           bufferToFill.clearActiveBufferRegion();


}

    }
    
    //==============================================================================
    
    float testFreq = 0;
    
    
    
    
    
    enum
    {
        fftOrder = 10,
        fftSizr = 16,
        fftSize  = 1<<fftSizr //65536
    };
    
    
    enum
    {
        fftOrder1 = 10,
        fftSize1 = 1 << fftOrder1
    };
    float num;
    struct table { float c; float s; float n; float f;};
    
    
            Path polPath;

        struct polygon { 
        
            float centerX;
         float centerY;
         float dx=0;
         float dy=0;
        bool caught = false;
                bool exited = true;

        
        
        
        };
        
vector<polygon> polygons;
                    float maxFrame = 0;
                    float lastMaxFrame = 0;

    void pushNextSampleIntoFifo (float sample) noexcept
    {
        // if the fifo contains enough data, set a flag to say
        // that the next line should now be rendered..
        /*
         if (fifoIndex == fftSize/16)
         {    fftspeed++;
         
         if (! nextFFTBlockReady)
         {
         int fifoSize =  sizeof(fifo)/sizeof(fifo[0]);
         float fftDataBuffer[fftSize*2];
         for (int n = 0; n<2 * fftSize; n++) fftDataBuffer[n] = fftData[n];
         for(int n = 0; n<fifoSize; n++) fftData[n] = fifo[n];
         for(int n = 0; n<2 * fftSize - fifoSize; n++) fftData[n +  fifoSize] = fftDataBuffer [n + fifoSize];
         nextFFTBlockReady = true;
         
         }
         
         fifoIndex = 0;
         }
         
         fifo[fifoIndex++] = sample;*/
        
        if (fifoIndex1 == fftSize1)
        {
            
            if (! nextFFTBlockReady1)
            {
                
                zeromem (fftDataC, sizeof (fftDataC));
                memcpy (fftDataC, fifo1, sizeof (fifo1));
                nextFFTBlockReady1 = true;
                lastMaxFrame = maxFrame;
                //lastMaxFrame /= 2;
                maxFrame = 0;
                for (auto i = 0; i < fftSize1; ++i) if(  fftDataC[i]>maxFrame)maxFrame = fftDataC[i];
                    for (auto i = 0; i < fftSize1; ++i) fftDataC[i] /= maxFrame*500;
                        for (int f = 0; f<bufferSize; f++){audioBuf[f]=fftDataC[f];spiraAudio[f] =fftDataC[f];}
                
                
            }
            fifoIndex1 = 0;
        }
        fifo1[fifoIndex1++] = sample;
        
    }
    
    
    dsp::FFT forwardFFT;
    dsp::FFT forwardFFT1;
    dsp::FFT forwardFFT11;
    Image spectrogramImage;
    
    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    
    
    float fifo1 [fftSize1];
    float fftData1 [2*fftSize1];
    int fifoIndex1 = 0;
    bool nextFFTBlockReady1 = false;
    
    float fftDataC [2 * fftSize1];
    
    OpenGLContext openGLContext;
    
    
#define CUTOFF 0.47 //0.97 is default
#define SMALL_CUTOFF .17
#define LOWER_PITCH_CUTOFF 80 //hz
    
    float getPitch(float *audioBuffer)
    {   
 

        std::vector<float> _nsdf = nsdfFrequencyDomain(audioBuffer);
        
        std::vector<int> max_positions = peak_picking(_nsdf);
        
        std::vector<std::pair<float, float>> estimates;
        
        float highestAmplitude = - 5000000;
        
        for (auto tau : max_positions)
        {
            highestAmplitude = jmax(highestAmplitude, _nsdf[tau]);
            
            if (_nsdf[tau] > SMALL_CUTOFF)
            {
                auto x = parabolic_interpolation(_nsdf, tau);
                estimates.push_back(x);
                highestAmplitude = std::max(highestAmplitude, std::get<1>(x));
            }
        }
        
        if (estimates.empty()) return -1;
        
        float actualCutoff = CUTOFF * highestAmplitude;
        float period = 1;
        
        for (auto estimate : estimates)
        {
            if (std::get<1>(estimate) >= actualCutoff)
            {
                period = std::get<0>(estimate);
                break;
            }  
        }
        
        float pitchEstimate = (sampleRate / period);
       // for(int n = 14; n>0; n--)  if (abs(pitchEstimate-pow(2,n))<.1)pitchEstimate=-2;
        if (pitchEstimate> LOWER_PITCH_CUTOFF) return  pitchEstimate;
        else return -1;
        
    }
    
    
    
    static const int fftSizep = fftSize1;
    static const int bufferSize = fftSizep;
    
    
    
    float turningPointX, turningPointY;
    
    
    
    inline std::pair<float, float> parabolic_interpolation(std::vector<float> array, float x)
    {
        int x_adjusted;
        
        if (x < 1) {
            x_adjusted = (array[x] <= array[x+1]) ? x : x+1;
        } else if (x > signed(array.size())-1) {
            x_adjusted = (array[x] <= array[x-1]) ? x : x-1;
        } else {
            float den = array[x+1] + array[x-1] - 2 * array[x];
            float delta = array[x-1] - array[x+1];
            return (!den) ? std::make_pair(x, array[x]) : std::make_pair(x + delta / (2 * den), array[x] - delta*delta/(8*den));
        }
        return std::make_pair(x_adjusted, array[x_adjusted]);
    }
    
    static std::vector<int> peak_picking(std::vector<float> nsdf)
    {
        std::vector<int> max_positions{};
        int pos = 0;
        int curMaxPos = 0;
        ssize_t size = nsdf.size();
        
        while (pos < (size - 1) / 3 && nsdf[pos] > 0) pos++;
        while (pos < size - 1 && nsdf[pos] <= 0.0) pos++;
        
        if (pos == 0) pos = 1;
        
        while (pos < size - 1) {
            if (nsdf[pos] > nsdf[pos - 1] && nsdf[pos] >= nsdf[pos + 1]) {
                if (curMaxPos == 0) {
                    curMaxPos = pos;
                } else if (nsdf[pos] > nsdf[curMaxPos]) {
                    curMaxPos = pos;
                }
            }
            pos++;
            if (pos < size - 1 && nsdf[pos] <= 0) {
                if (curMaxPos > 0) {
                    max_positions.push_back(curMaxPos);
                    curMaxPos = 0;
                }
                while (pos < size - 1 && nsdf[pos] <= 0.0) {
                    pos++;
                }
            }
        }
        if (curMaxPos > 0) {
            max_positions.push_back(curMaxPos);
        }
        return max_positions;
    }
    
    std::vector<float> nsdfFrequencyDomain (const float *audioBuffer)
    {
        
        std::vector<float> acf (autoCorrelation (audioBuffer));
        return acf;
    }
    std::vector<float> autoCorrelation(const float *audioBuffer)
    {
        float audioProcesse[bufferSize*2];
        for(int l = 0; l<bufferSize; l++) audioProcesse[l] = audioBuf[l]*5000000*-sin(pi*l/bufferSize);
        forwardFFT1.performRealOnlyForwardTransform      (audioProcesse);
        
        for (int i = 0; i < fftSizep-1; i+=2)
        {
            
            std::complex<float> complex(audioProcesse[i], audioProcesse[i+1]);
            complex = complex * std::conj(complex);
            audioProcesse[i] = complex.real();
            audioProcesse[i+1] = complex.imag();
            
        }
        
        forwardFFT1.performRealOnlyInverseTransform     (audioProcesse)     ;
        vector<float> x;
        for (int i = 0; i < bufferSize; ++i)
            x.push_back( audioProcesse[i]);
        return x;
    }
    
    
    
    
    
    
    
    
    
    
    
    float fftDataB[bufferSize];
    
    float audioBuf[bufferSize];
    float spiraAudio[bufferSize];
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Radial_eq)
};
#endif  // radial_eq_INCLUDED

