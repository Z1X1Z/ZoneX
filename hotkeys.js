let leaf = -1.3247179572447460259609088544780973407344040569017333645340150503028278512455475940546993479817872803299109209947422074251089026390458977955943147570967234717541668390388674187517369315842535499082466223545337273504589879909568150627745509802486213012169894157524574548625075626524610368938904839932269952074975962828868556908150704513696109853352577281586033441141927828273765296032993584674231028483241695239006108543338219;
let gr = 1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538689175212663386222353693179318006076672635443338908659593958290563832266131992829026788067520876689250171169620703222104321626954862629631361443814975870122034080588795445474924618569536486444924104432077134494704956584678850987433944221254487706647
let leaf2 = - 1.3472963553338606977034332535386295920007513543681387744724827562641316442780294708430332263148;
let grgr2 = 2.5320888862379560704047853011108333478716649141607904917080905692843107777137494470564585533611;
//https://www.wolframalpha.com/input?i=a%3D%28%281-%28%281-%28%281-a%29%5E2-1%29%29%5E2-1%29%29%5E2-1%29
window.pixelShaderSize = 7;
const pixelShaderToStarshipRATIO = pixelShaderSize/4.;//don't change from 7./4. or some factor of 7 seems right;
const movementRateORIGINAL = 1.;
const starshipSize = Math.E**leaf/Math.sqrt(2.);//divided by Math.sqrt(2.) to set trail to equilateral,other coefficients are scale (size)
                            const zoomFrames = 60;//frames to double zoom
let ZR = Math.E**(Math.log(.5)/zoomFrames);
                  let mf = (Math.max(window.innerHeight,window.innerWidth)/Math.min(window.innerHeight,window.innerWidth));//advantage of translation over zoom (right?)
let MR = mf/zoomFrames;
const secondsToEdge=window.pixelShaderSize/4./pixelShaderToStarshipRATIO;

window.uniformsInitial = {
coreDilation:{value:0.},
fftSize:{value:2048.},sampleRate:{value:44100.}, nyq:{value:1024./44100.},//actually 2/nyquist
    
zoomOutRatchetThreshold:{value:0.},
radialWarp:{value:1.},
pixelSTARon:{value:true},
pongOn:{value:true},
heartStar:{value:0},
superStable:{value:false},
distributor:{value:true},

micIn:{value:null},
    audioBuffer:{value:null},
    omniDynamic:{value:null},
videoTexture:{value:null},
videoTexture2:{value:null},
coreTextureSampler:{value:null},
STAR:{value:null},
EDEN:{value:null},
uberDuper:{value:null},
    
        eden:{value: 0},
        spokesVisualizeColors: {value: false    },
        note:{value: 48.},
        brelued:{value: 1.},
        balloonsON:{value: 0.},
        balloonsONexponential:{value: 0.},
        sparklesON:{value: false},
        SPHEREofTheLORD:{value: false},
            
        clvrVariant1:{value: false},
        clvrVariant2:{value: false},
        clvrVariant3:{value: false},
        clvrVariant4:{value: true},
        clvrVariant5:{value: false},
        clvrVariant6:{value: false},
        clvrVariant7:{value: false},
clvrVariant8:{value: false},
clvrVariant9:{value: false},
clvrVariant0:{value: false},

twelveGates:{value: false    },
twelveGatesMeta:{value: .4    },
Spoker:{value: true    },
        spokelover:{value: true    },
largeEyeColor:{value:0.},
holyeyes:{value:1},
    
    
dilate:{value:true},

    
        continuumClover:{value: false    },
        Inherited:{value: true    },
        cloverSlide:{value: false    },
        Pointers:{value:true},
        time: {value:.0 },
        rate: {value: 1.},

        zoom: {value:  .99},
        colorCombo: {value: -1 },
        free: {value: false },
        MetaCored: {value: true },
        externalCores: {value: 0. },
        centralCores: {value: 0. },
        outerCoresOff: {value: false},
        upCoreCycler: {value: 0. },

        morph: {value: 0.0 },

        fourCreats: {value: 1 },
        Character: {value: 0 },
        articles: {value: false },
        helm: {value: false },
        wheel: {value: false },
        Refractelate: {value: false },
        petals: {value:  .0 },

        carousel: {value: 0.0 },
        metaCarousel: {value: 0. },
        spirated: {value: 0. },
        hearTOL: {value: false},
        colorInverter: {value:false},
        metronome: {value: .99 },
        time2dance: {value: 0.0 },
        volume: {value: .0 },
        totalAmp: {value: 1.0 },


        resolution: {value:[window.innerWidth,window.innerHeight]},//these are later resolved to the THREE.vec2() uniforms
        coords: {value: [0.,0.]},//to prevent dividing by zero may be set to small value
        coordSHIFT: {value: [0.,0.]},
        d: {value:[.4,.7]},
dotCoord:{value:[0.,0.]},
pongBallCoords:{value:[0.,window.innerWidth/gr]},

duperZoom: {value:1.},

        dynamicDance: {value: 0},
        remediatedColors: {value: false },

        Clovoid:{value:false},
        dotted:{value:false},
    baseN:{value: 2.701002244218596767553929329640246633},//e=2.718281828},2.84657807422=pi*e/3//2.7010022442185967675539293296402466332894763318949646518637734692=(pi*e)^2/3^3

        onehundredfortyfourthousand:{value:false},
        shaderScale:{value:window.pixelShaderSize},
        starSpin:{value:0.},
        chirality:{value:1},
        MannyONtrail:{value:0},
        NightAndDay:{value:false},
        starOnDot:{value:0},
        gameOn:{value:false},
        scoreLoaded:{value:false},
        musicAngelMan:{value:2},
        refactorCores:{value:1.},

        fieldPowerBoost:{value:false},
        fieldPowerBoostMeta:{value:false},
        flipStar:{value:1.},
        witnessFlip:{value:1.},
        twistStar:{value:0.},
        multiplicatorNexus:{value:false},//has problems may be discontinued
        squareClover:{value:false},
        mandelCloverFactor:{value:.26},
exponentialPetals:{value:0.},
cloverOffset:{value:0.},
spinTowardsMe:{value:false},
chop:{value:false},
whirlpool:{value:0},
armsSpinning:{value:1},
maxSamp:{value:0.},
minSamp:{value:0.},
lownote:{value:0.},
gates:{value:true},
leaf:{value:leaf},
gr:{value:gr}
        }
window.uniforms={}

let runningHash = true;
window.settingsSet = false












function resetAll(){
    for(var nameOfUniform in uniformsInitial)
    {
        window.uniforms[nameOfUniform]={}
        Object.assign(window.uniforms[nameOfUniform],window.uniformsInitial[nameOfUniform])
    }
    if(window.touchOnlyMode)window.uniforms.pongOn.value=false;
    window.coordX=0.; window.coordY=0.;
    
    
    if(!location.hash.includes(".b")&&!location.hash.includes(".c")) window.BibleON=1;
    else window.BibleON=0;
    if(settingsSet)
    {
        if(location.hash.includes(".b")||location.hash.includes(".c")) window.BibleON=1;
        else window.BibleON=0;
        
        if(window.useCDN||location.hash.includes(".b")||location.hash.includes(".c"))
            callKey(new KeyboardEvent('keydown', {'key': "b", 'altKey':true, 'keyCode':key.charCodeAt(0)}));
    }
    window.DAW=false;
    if(!("DAWSonicTouchArray" in window))    window.DAWSonicTouchArray=[];
        window.osmdSound = false;
    
    window.leafMode=0;
    window.xTouch=0;
    window.yTouch=0;
    window.xTouchMicroBuffer=0./10000.;
    window.yTouchMicroBuffer=-1./10000.;
    window.touchVolume = .5;
    window.radialOctaveBoost = false;
    window.twist = 0.;
    window.skew = 0.;
    window.flip = 1.;
    window.cycleCores = false;
    window.sheetTranslucent=false;
            window.FPS=60;
            window.zoom=1.;
            window.ISdilated=false;
            window.RockInTheWater=0;
            window.octaveStars=true;
            window.BulletMine=0;
            window.starClover=true;
            window.blankBackground=false;
            window.twist = 0.;
            window.flip = 1.;
            window.highORlow=0.;
            window.FeedbackSound = false;
            window.spirographMODE = 1;
            window.pzyghthe=0;
            window.dynamicCoring=false;
            window.omniDynamicEngaged=false;

    window.ballVectorX = 1.;
    window.ballVectorY= 1.;
    
            window.fftSize = 2048;
            window.starArms = fftSize/2.
    
  window.video = null;
  window.videoCanvas = null;
    window.video2 = null;
    window.videoCanvas2 = null;
    window.streaming=false;
    window.streaming2=false;
    window.Oreo=true;
            window.shouldShowStar = true;
            window.flame = false;
            window.muteTouchTouchVolume = true;
            window.muteVoiceTouchVolume = false;
            window.grabStar = false;



            window.movementRate=movementRateORIGINAL;
            window.zoomRate=movementRateORIGINAL;
            window.radialWarp=1.;
            window.trailSecondsLong = secondsToEdge/movementRate*7.;
            window.trailLength = Math.ceil(zoomFrames*trailSecondsLong);
            window.starShipDepthInSet = (trailSecondsLong-pixelShaderToStarshipRATIO/2.)/trailSecondsLong;
            window.starCount = Math.ceil(starArms*60*secondsToEdge);

           // if(!window.touchOnlyMode||location.hash.includes("t"))
                                         window.touchMode=false;
            window.volumeSpeed = false;
             window.totalAMP=1;
                                         window.front = 1;
            window.center = false;
            window.zoomOutRatchetThreshold= 1./1024;

            window.ConcertKey = 440;

            window.textON=false;
            window.dupered = false;
            window.haptic = false;
            window.haptic2 = false;
            window.zoomAtl41=false;//watch for the 1 and the l

            window.onO = false;
    window.EldersLeg = 24;
                                         
                       window.coreData = new Float32Array(40).fill(1./-leaf);
                       window.omniData = new Float32Array(40).fill(0.);
                                         
                                             if (   window.iOS )window.rez=window.devicePixelRatio/4.;
                                               else if(window.android)window.rez=window.devicePixelRatio/5.;
                                               else   window.rez=window.devicePixelRatio/2.;
                                                   
    if(window.INITIALIZED){
                setVectors();
        setFFTdependantSizes();
                setDAWdependantSize();
        setDynamicSampler2ds();
        setMicInputToStarPIXEL();
        setTrailSize()
        renderer.setPixelRatio( rez)
                onWindowResize();
    }
    if(wadLOADED)
    {
                for(var o=0;o<maxTouchSoundCount;o++){
                    stopSounds(SonicTouchArray[o])

                    }
                for(var o=0;o<DAWSonicTouchArray.length;o++){
                    stopSounds(DAWSonicTouchArray[o])

                  //  DAWnodeIndexForTouchBestFitIndex[o]="not set"
                   }
                
                for(var o=0;o<window.osmdOscillators;o++)
                {singAlong[o].stop();
                    singAlong2[o].stop();
                }

    }
                                         window.DAWSonicTouchArray=[];

                                         
                                         window.screenPressCoordX=Array(maxTouchSoundCount).fill(0);
                                         window.screenPressCoordY=Array(maxTouchSoundCount).fill(0);

                                         
                                         runningHash = true;
                                         window.number = "no number";

                                       if(window.settingsSet)  readHash()
                                         
                                         let n = document.getElementsByName('t');
                                          for(var p = 0; p<n.length;p++)n[p].checked  = false;
                                         
                                         window.settingsSet = true
                                         
}
resetAll();


let osmdStaffsVisible = 0;
window.number = "no number";
                                         
                               let          hashHasRun = false;
function readHash(){
        let hashindex = 0;
        while (hashindex<location.hash.length)
        {
            number=""
            let lasthash = hashindex;
            let ALT = location.hash[hashindex-1]=="."||location.hash[hashindex-2]==".";
            let CTRL = location.hash[hashindex-1]==","||location.hash[hashindex-2]==",";
            let bibleReaderCode =(location.hash[hashindex-2]=="c"&&location.hash[hashindex-3]==".")
                                ||(location.hash[hashindex-1]=="b"&&location.hash[hashindex-2]==".")
            if(location.hash[hashindex+1]=="(")
            {            hashindex++;hashindex++;
                
                while(location.hash[hashindex]!=")"&&hashindex!=location.hash.length)
                {
                    number += location.hash[hashindex]
                    hashindex++;
                }
                

                   
                
            }
            
            if (number === "")
                number = "no number"
           if(!bibleReaderCode) callKey(new KeyboardEvent('keydown',
                                      {
                'key': location.hash[lasthash],"keyCode":location.hash.charCodeAt(lasthash),
                "ctrlKey":CTRL,"altKey":ALT
            }                              ));
            
            hashindex++;
            
            
        }
        runningHash=false;
                hashHasRun = true;
}
readHash();
function hk() {
  var x = document.createElement("INPUT");
  x.setAttribute("type", "text");
  x.setAttribute("id", "hotkeys");
  x.setAttribute("placeholder", "Hotkeys!");
  x.setAttribute("oninput", "getKey()");
  document.getElementById("hotkeyHolder").appendChild(x);

}
let hotkeyInputWindowActive = false;
if(mobile)
    hk();



let androidGetKey="";
let androidGetKeyLast="";

function getKey(){
    androidGetKeyLast = androidGetKey;
    androidGetKey = document.getElementById("hotkeys").value;
    let keyCaught;
 let scan=androidGetKey.length-1;
  while(scan>=0){
        if(androidGetKey[scan]!=androidGetKeyLast[scan])keyCaught=androidGetKey[scan];
        scan--;
        }
   callKey(new KeyboardEvent('keydown', {'key': keyCaught, "keyCode":keyCaught.charCodeAt(0)}));
}



if(!mobile)//)//if not mobile
window.addEventListener('keydown', function(event) {callKey(event); return true;}, false);

    window.lastKey = "";
window.key = " ";
                                         function callKey(event){
                window.lastKey = window.key;
                if(lastKey==","&&!runningHash)//key here is the last key
                    event=new KeyboardEvent('keydown',
                                            {"key":event.key,"keyCode":event.keyCode,"ctrlKey":true}
                                            );
                else if(lastKey=="."&&!runningHash)event=new KeyboardEvent('keydown',
                                                                           {"key":event.key,"keyCode":event.keyCode,"altKey":true}//creating a new keypress because it's readonly
                                                                           );
                
                key = event.key;
                //number=Number(number);
                if(key=="/"&&!event.shiftKey){  event.preventDefault(); event.stopImmediatePropagation();}
                
                var x=null;
                if(!event.shiftKey)x = parseInt(String.fromCharCode( event.keyCode));
                
                
                //meta keys like ctrlKey must be processed first and should have symbol preferably
                if(key == "q" && event.altKey&&event.ctrlKey)
                {
                    uniforms.gates.value=!uniforms.gates.value
                    
                }
                else if(key == "z" && event.altKey&&event.ctrlKey)
                {
                    leafMode=(leafMode+1)%2.
                    if(leafMode==0)
                    {
                        leaf = -1.3247179572447460259609088544780973407344040569017333645340150503028278512455475940546993479817872803299109209947422074251089026390458977955943147570967234717541668390388674187517369315842535499082466223545337273504589879909568150627745509802486213012169894157524574548625075626524610368938904839932269952074975962828868556908150704513696109853352577281586033441141927828273765296032993584674231028483241695239006108543338219;
                        gr = 1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538689175212663386222353693179318006076672635443338908659593958290563832266131992829026788067520876689250171169620703222104321626954862629631361443814975870122034080588795445474924618569536486444924104432077134494704956584678850987433944221254487706647
                        uniforms.leaf.value=leaf;
                        uniforms.gr.value=gr;
                    }
                    else
                    {
                        leaf =leaf2;// -leaf2/leaf*4./3.
                       // gr = grgr2/gr
                        
                        uniforms.leaf.value=leaf;
                        uniforms.gr.value=gr;
                    }
                }
            
    else if(key == "o" && event.ctrlKey)
    {
        omniDynamicEngaged = !omniDynamicEngaged;
        if(!omniDynamicEngaged)omniData.fill(0);
    }
                
             else   if(key == "u" && event.ctrlKey)
                    uniforms.pongOn.value = !uniforms.pongOn.value;
    else if(key == "c" && event.ctrlKey){dynamicCoring=!dynamicCoring; if(!dynamicCoring)coreData.fill(document.getElementById('coringConstant').value);}
               else if(key == "h" && event.ctrlKey)uniforms.spinTowardsMe.value=!uniforms.spinTowardsMe.value
                   else if(key == "e" && event.ctrlKey)uniforms.chop.value=!uniforms.chop.value;
    else if(key == "q" && event.ctrlKey)uniforms.squareClover.value=!uniforms.squareClover.value;
    else if(key == "x" && event.ctrlKey)uniforms.fieldPowerBoost.value=!uniforms.fieldPowerBoost.value;
    else if(key == "z" && event.ctrlKey)uniforms.fieldPowerBoostMeta.value=!uniforms.fieldPowerBoostMeta.value;
    else if(key == "b" && event.ctrlKey){
        uniforms.balloonsONexponential.value = 0.;
        if(uniforms.balloonsON.value==0.)uniforms.balloonsON.value=1.
            else if(uniforms.balloonsON.value==1.)uniforms.balloonsON.value=-1.
                else  if(uniforms.balloonsON.value==-1.)uniforms.balloonsON.value=0.
                    }
    else if(key == "n" && event.ctrlKey){
        uniforms.balloonsON.value=0.;
        if(uniforms.balloonsONexponential.value==0.)uniforms.balloonsONexponential.value=1.
            else if(uniforms.balloonsONexponential.value==1.)uniforms.balloonsONexponential.value=-1.
                else  if(uniforms.balloonsONexponential.value==-1.)uniforms.balloonsONexponential.value=0.;
                    }
    else if(key == "s" && event.ctrlKey)uniforms.sparklesON.value=!uniforms.sparklesON.value;
    else if(key == "f" && event.ctrlKey)uniforms.SPHEREofTheLORD.value=!uniforms.SPHEREofTheLORD.value;
    else if(key == "k" && event.ctrlKey)
    {
        window.timeRESET= window.TIMESTAMP;
        if(window.ChristoDecrypto==0.)
        {
            window.ChristoDecrypto = leaf;
            if(uniforms.metaCarousel.value==0)uniforms.metaCarousel.value=0;
        }
        else
        {
            window.ChristoDecrypto = 0 ;
            uniforms.metaCarousel.value=0.;
        }
    }
    else if(key == "v" && event.ctrlKey) window.FeedbackSound =  !window.FeedbackSound;
    else if(key == "d" && event.ctrlKey)uniforms.starOnDot.value=(uniforms.starOnDot.value+1)%3;
    else if (key=="p" && event.ctrlKey)spirographMODE = (spirographMODE+1)%3;//color mode 3 seems obsolete
    //else if (key=="m" && event.ctrlKey)uniforms.multiplicatorNexus.value=!uniforms.multiplicatorNexus.value;

    else if (event.ctrlKey&&key=="a")uniforms[ "colorCombo" ].value = 11;
    else if (event.ctrlKey&&key=="j")window.Oreo=!window.Oreo;
    else if (event.ctrlKey&&key=="t")window.shouldShowStar=!window.shouldShowStar;
    else if (event.ctrlKey&&key=="r")window.flame=!window.flame;
    else if (event.ctrlKey&&key=="l")         uniforms.holyeyes.value=(uniforms.holyeyes.value+1)%4;

    else if (event.ctrlKey&&key=="g") {
        if( uniforms.exponentialPetals.value==0.) uniforms.exponentialPetals.value=1.;
        else if( uniforms.exponentialPetals.value==1.) uniforms.exponentialPetals.value=-1.;
        else if( uniforms.exponentialPetals.value==-1.) uniforms.exponentialPetals.value=0.;
        
    }
    else if (event.altKey&&(key=="i"||key=="ˆ"))//dead
    {
       if( uniforms.whirlpool.value==0) uniforms.whirlpool.value=1;
        else if ( uniforms.whirlpool.value==1) uniforms.whirlpool.value=-1;
        else if  (uniforms.whirlpool.value==-1) uniforms.whirlpool.value=0;
    }

    else if (event.altKey&&(key=="˜"||key=="ñ"||key=="n"))//dead
        uniforms.twelveGates.value=!uniforms.twelveGates.value;
    else if (event.altKey&&(key=="∆"||key=="j"))
    {
        uniforms.Pointers.value=!uniforms.Pointers.value;
    }
    else if (event.altKey&&(key=="ç"||key=="c"))uniforms.distributor.value = !uniforms.distributor.value;//hotkey seems to already be in use for bible chapter

    else if (event.altKey&&(key=="µ"||key=="m"))
    {if(number!="no number")
        uniforms.twelveGatesMeta.value=number;
    else if( uniforms.twelveGatesMeta.value==2.)uniforms.twelveGatesMeta.value=0
        else  uniforms.twelveGatesMeta.value=2;
        
    }


    else if (event.altKey&&(key=="∑"||key=="w"))window.DAW=!window.DAW;
    else if (event.altKey&&(key=="´"||key=="e"))(window.highORlow=window.highORlow+1)%3;

    else if (event.altKey&&(key=="¥"||key=="y"))
    {
        if(uniforms.largeEyeColor.value==0.)uniforms.largeEyeColor.value = -1.;
        else if(uniforms.largeEyeColor.value==-1.)uniforms.largeEyeColor.value = 1.;
        else if(uniforms.largeEyeColor.value==1.)uniforms.largeEyeColor.value = 3.;
        else if(uniforms.largeEyeColor.value==3.)uniforms.largeEyeColor.value = 0.;

    
    }
    else if (event.altKey&&(key=="˙"||key=="h")) uniforms.heartStar.value=(uniforms.heartStar.value+1)%4;
    else if (event.altKey&&(key=="œ"||key=="q")){
            if          ( uniforms[ "colorCombo" ].value >1)          uniforms[ "colorCombo" ].value = -1;
            else uniforms[ "colorCombo" ].value = -(Math.abs(uniforms[ "colorCombo" ].value+1-17.))%17;
        }

    else if (event.altKey&&(key=="≈"||key=="x")){ if(!runningHash||!window.online) uniforms.brelued.value*=-1;}
    else if (event.altKey&&(key=="Ω"||key=="z"))uniforms.witnessFlip.value*=-1.;
    else if (event.altKey&&(key=="π"||key=="p"))uniforms.pixelSTARon.value=!uniforms.pixelSTARon.value;
    else if (event.altKey&&(key=="©"||key=="g"))window.grabStar=!window.grabStar;
    else if (event.altKey&&(key=="ß"||key=="s")){
        if(window.touchMode||window.touchOnlyMode)window.muteTouchTouchVolume = !window.muteTouchTouchVolume;
        else window.muteVoiceTouchVolume = !window.muteVoiceTouchVolume;
    }
    else if (event.altKey&&(key=="∫"||key=="b")){
                 if(!muteToggle&&!runningHash)
                       window.BibleON = (window.BibleON+1)%2;

        let content = document.getElementsByClassName("dropdown-content");
        //iframe redirect from https://stackoverflow.com/questions/28159920/how-to-redirect-page-inside-iframe-to-another-one-but-we-must-stay-in-iframe
        if(runningHash
           
           );//dynamic href for iFrame doesn't seem to work on mobile
        else if (number == 8)
        
            window.frames["TheBible"].location = "https://openbible.com/audio/gilbert_music/";
        
                else if(number ==7) window.frames["TheBible"].location ="https://openbible.com/audio/gilbert_music_books/";
                else if(number == 6)   window.frames["TheBible"].location =
                    "https://openbible.com/audio/hays/";
                else if(number == 5)  window.frames["TheBible"].location =  "https://openbible.com/audio/souer/";
                else if(number == 4)  window.frames["TheBible"].location =  "https://openbible.com/audio/gilbert/";
            else if(number == 3)  window.frames["TheBible"].location = "https://openbible.com/audio/hays_books/";
            else if(number == 2)  window.frames["TheBible"].location =  "https://openbible.com/audio/souer_books/";
        else if(number == 1)  window.frames["TheBible"].location =  "https://openbible.com/audio/gilbert_books/";
         else if(number== 0)  window.frames["TheBible"].location =  "https://www.biblehub.com/audio/";
         else if (!window.readerSet){
             window.frames["TheBible"].location =  "https://www.biblehub.com/audio/";
             window.readerSet=true;
         }
             //   else if(location.hash.includes(".b"))document.getElementById("reader").value = 0.;
       // else if (window.frames["TheBible"].location=="about:blank")window.frames["TheBible"].location="https://www.biblehub.com/audio/"
                    if(window.BibleON==0)
                    {
                        document.getElementById("Bible").height="100%";
                        document.getElementById("Bible").width="100%";
                        document.getElementById("nav").style.width="50%";
                        document.getElementById("menuDivider").style.width="50%";

                        for(var b = 0; b<content.length; b++)content[b].style.width="50%";
                    }
                    else {
                        document.getElementById("Bible").height= "0%";
                        document.getElementById("Bible").width="0%";
                        document.getElementById("nav").style.width="100%";
                        for(var b = 0; b<content.length; b++)content[b].style.width="100%";
                        document.getElementById("menuDivider").style.width="100%";

                        
                    }
                
                 if(window.INITIALIZED) onWindowResize();
                            
    }//bible iframe loaded in manny.html
    else if (event.altKey&&(key=="¬"||key=="l"))
    {
        if(!streaming)
        {
        //https://developer.mozilla.org/en-US/docs/Web/API/Media_Capture_and_Streams_API/Taking_still_photos//
            window.video = document.getElementById('video');
            window.videoCanvas = document.getElementById('videoCanvas');
            navigator.mediaDevices
            .getUserMedia({ video: {
            facingMode: "user"
            }
                //https://stackoverflow.com/questions/64553141/html-usermedia-facingmode-environmentdoesnt-work-on-android-phone
                
            })
            .then((stream) => {
                
                window.video.srcObject = stream;
                window.video.play();
            })
            .catch((err) => {
                console.error(`An error occurred: ${err}`);
            });
            
            video.oncanplay=
                                   (ev) => {
                                       if (!streaming) {
                                           video.setAttribute("width", window.innerWidth);
                                           video.setAttribute("height", window.innerHeight);
                                           
                                           videoCanvas.setAttribute("width", window.innerWidth);
                                           videoCanvas.setAttribute("height", window.innerHeight);
                                           streaming = true;
                                       }
                                   }
            
            
        }
        else streaming=false;
        }
    else if (event.altKey&&(key=="√"||key=="v"))
    {
        //https://developer.mozilla.org/en-US/docs/Web/API/Media_Capture_and_Streams_API/Taking_still_photos//
        window.video2 = document.getElementById('video2');
        window.videoCanvas2 = document.getElementById('videoCanvas2');
        if(!streaming2){
        navigator.mediaDevices
        .getUserMedia({ video: {
        facingMode: "environment"
        }
        })
        .then((stream) => {
            window.video2.srcObject = stream;
            window.video2.play();
        })
        .catch((err) => {
            console.error(`An error occurred: ${err}`);
        });
        video2.oncanplay=
        (ev) => {
            if (!streaming) {
                video2.setAttribute("width", window.innerWidth);
                video2.setAttribute("height", window.innerHeight);
                
                videoCanvas2.setAttribute("width", window.innerWidth);
                videoCanvas2.setAttribute("height", window.innerHeight);
                streaming2 = true;
            }
        }
    }
        else streaming2=false;


    }
    else if(number=="no number"&&Number(x)==x&&event.altKey&&!event.shiftKey)
    {
        if(x == 0)uniforms.clvrVariant0.value=!uniforms.clvrVariant0.value;
        if(x == 1)uniforms.clvrVariant1.value=!uniforms.clvrVariant1.value;
        else if(x == 2)uniforms.clvrVariant2.value=!uniforms.clvrVariant2.value;
        else if(x == 3)uniforms.clvrVariant3.value=!uniforms.clvrVariant3.value;
        else if(x == 4)uniforms.clvrVariant4.value=!uniforms.clvrVariant4.value;
        else if(x == 5)uniforms.clvrVariant5.value=!uniforms.clvrVariant5.value;
        else if(x == 6)uniforms.clvrVariant6.value=!uniforms.clvrVariant6.value;
        else if(x == 7)uniforms.clvrVariant7.value=!uniforms.clvrVariant7.value;
        else if(x == 8)uniforms.clvrVariant8.value=!uniforms.clvrVariant8.value;
        else if(x == 9)uniforms.clvrVariant9.value=!uniforms.clvrVariant9.value;
    }
    else if((key=="†"||key=="t")&&event.altKey&&!event.shiftKey)// is alt+a
    {
        window.pzyghthe = (window.pzyghthe+1.)%5;
       // if(pzyghthe==0) scene.remove(harmonicPzyghtheMesh);
        //else if (pzyghthe==1) scene.add(harmonicPzyghtheMesh)
            
            
            }
    
    else if((key=="å"||key=="a")&&event.altKey&&!event.shiftKey)// is alt+a
        uniforms.musicAngelMan.value=(uniforms.musicAngelMan.value+1)%3;
    else if((key=="®"||key=="r")&&event.altKey&&!event.shiftKey)//® is alt+r
    {
        if(uniforms.refactorCores.value==2)uniforms.refactorCores.value=1;
        else if(uniforms.refactorCores.value==1)uniforms.refactorCores.value=0;
        else uniforms.refactorCores.value=2;
    }
                
                else if (event.altKey&&(key=="∂"||key=="d"))//∂ is alt+d
                    uniforms.armsSpinning.value=           (uniforms.armsSpinning.value+1)%5//more modes were found unstably

                else if (event.altKey&&(key=="ø"||key=="o")) {
                    uniforms.dilate.value=!uniforms.dilate.value;

                   // window.ISdilated=!window.ISdilated;//this is for dilator in wadloader which this superceded
                  //  console.log(ISdilated)
                }


                
                
                else if((key=="˚"||key=="k")&&event.altKey&&!event.shiftKey) window.radialOctaveBoost=!window.radialOctaveBoost;
                else if((key=="…"||key==";")&&event.altKey&&!event.shiftKey) uniforms.superStable.value=!uniforms.superStable.value;
       
                
    else if (event.altKey&&key=="f")console.log("speakers disabled!");//speakers turned off in manny.html
                
    else if(event.ctrlKey||event.altKey);//swallow remaining possibilities, muting keypress
    /*if(key == "k" && event.ctrlKey)
     {
     osmdStaffsVisible=(osmdStaffsVisible+1)%3;
     if("osmd" in window&&osmd!=null&&osmd.sheet.Instruments.length>=2)
     {
     if(osmdStaffsVisible==0)
     {
     osmd.sheet.Instruments[0].Visible = true;
     osmd.sheet.Instruments[1].Visible = false;
     }
     else if(osmdStaffsVisible==1)
     {
     osmd.sheet.Instruments[0].Visible = false;
     osmd.sheet.Instruments[1].Visible = true;
     }
     else if(osmdStaffsVisible==2)
     {
     
     osmd.sheet.Instruments[0].Visible = true;
     osmd.sheet.Instruments[1].Visible = true;
     }
     
     osmd.render();
     }
     } the bass staff doesn't include the lyrics so it's not included
     */
    else  if (key=="a"){if(number!="no number"){
        if(number>=1.)
        EldersLeg=Math.round(number)*1.;
        else if(number!=0.) EldersLeg=-1;
        let minimumFFTfactor = Math.ceil(Math.log(EldersLeg*12*2)/Math.log(2.));
        if(minimumFFTfactor<=15){
            if(minimumFFTfactor>11)//currently a buffersize of 2**11==2048 is required for spirograph
                fftSize=2**minimumFFTfactor;
            else
                fftSize = 2**11
                }
        if(!runningHash)
            setFFTdependantSizes();
        
    }}
    
    else if (key=="\\"){zoomRate=movementRateORIGINAL; if(number!="no number")
        zoomRate=number*1.;
    }

    else if (key=="/"){if(number!="no number"){trailSecondsLong=number*1.;
        if(window.INITIALIZED) setTrailSize()}}
    
    else if (x==0)
    {window.movementRate=movementRateORIGINAL; uniforms[ "rate" ].value=movementRateORIGINAL;
        if(number!="no number"){window.movementRate=number*1.; uniforms[ "rate" ].value=number*1.;};
    }
    
    else if (document.activeElement.className=="num");//don't take number hotkey's while menu number selector engaged
    
    else if (x>0&&x<=9&& document.activeElement.className!="num"&&!event.shiftKey&&!event.altKey)
    {rez = window.devicePixelRatio/x;
        if(window.INITIALIZED) renderer.setPixelRatio( rez);
    }
    
    /*else if (x==0&& document.activeElement.className!="num"&&!event.shiftKey&&!event.altKey)
     {rez = window.devicePixelRatio/10.; renderer.setPixelRatio( rez);}
     */
    else if (key=="+"){rez /=1.1; if(window.INITIALIZED) renderer.setPixelRatio( rez);}
    else if (key=="_"){rez *=1.1; if(window.INITIALIZED) renderer.setPixelRatio( rez);}
    
    else if (key=="À"||key=="`")
    {rez=window.devicePixelRatio*2.;
        if(window.INITIALIZED)   renderer.setPixelRatio( rez);}
    else if (key=="m"){
        
        uniforms[ "wheel" ].value = !uniforms[ "wheel" ].value;
        if( !uniforms[ "wheel" ].value)  uniforms["upCoreCycler"].value=0;
        if(number!="no number")uniforms.mandelCloverFactor.value=number;
    }
                
    else if (key=="M") uniforms[ "NightAndDay" ].value = !uniforms[ "NightAndDay" ].value;
    else if (key=="!")uniforms[ "Refractelate" ].value=!uniforms[ "Refractelate" ].value;
    else if (key=="@")uniforms[ "Clovoid" ].value=!uniforms[ "Clovoid" ].value;
    // else if (key=="#"){uniforms[ "base3" ].value=!uniforms[ "base3" ].value;console.log(uniforms[ "base3" ].value)}
    
    else if (key=="&")uniforms[ "continuumClover" ].value=!uniforms[ "continuumClover" ].value;
    
    
    else if (key=="q") {
        if          ( uniforms[ "colorCombo" ].value >1)          uniforms[ "colorCombo" ].value = -1;
        else uniforms[ "colorCombo" ].value = -(Math.abs(uniforms[ "colorCombo" ].value-1))%17;
    }
    
    else if (key=="Q") {
        window.twist = window.skew;
        if( uniforms.starSpin.value==0) uniforms.starSpin.value=1;
        else if( uniforms.starSpin.value==1) uniforms.starSpin.value=-1;
        else if( uniforms.starSpin.value==-1) uniforms.starSpin.value=0;
        
    }
    else if (key==";") uniforms[ "colorInverter" ].value = !uniforms[ "colorInverter" ].value;
    else if (key=="t"){
        window.touchMode = !window.touchMode;
        if (window.touchMode)window.shouldShowStar =false;
        else window.shouldShowStar = true;
    }
    else if (key=="T") uniforms.Spoker.value=!uniforms.Spoker.value;
    else if (key=="f") uniforms[ "fourCreats" ].value *= -1;
    else if (key=="F") uniforms[ "spokelover" ].value=!uniforms[ "spokelover" ].value ;
    
    else if (key=="\"") uniforms[ "colorCombo" ].value = 13;
    else if (key=="d") uniforms[ "colorCombo" ].value = 14;
    else if (key=="x")  uniforms[ "colorCombo" ].value = 15;
    
    else if (key=="*") uniforms[ "colorCombo" ].value = 20;
    
    else if (key=="X"){
        uniforms[ "dynamicDance" ].value = !uniforms[ "dynamicDance" ].value;
        window.date = Date.now();
        window.startTimeSecondMantissaMagnified = ((date/1000.-Math.round(date)/1000.)-.5)*144000;//for orienting the dance to time
    }
    else if (key=="b") window.cycleCores = !window.cycleCores;
    else if (key=="B") {
        if(BulletMine == 0) BulletMine = 1;
        else if(BulletMine==1) BulletMine = -.5;
        else if(BulletMine==-1) BulletMine = 0;
    }
    else if (key=="g") uniforms[ "colorCombo" ].value = 17;
    else if (key=="G") uniforms[ "articles" ].value = !uniforms[ "articles" ].value;
    
    else if (key=="r"){uniforms[ "colorCombo" ].value = 18;}
    else if (key=="$")uniforms[ "colorCombo" ].value = 19;
    
    else if (key=="s"){ if(uniforms[ "morph" ].value == 0.)uniforms[ "morph" ].value = 1.;else uniforms[ "morph" ].value = 0.; }
    else if (key=="n") uniforms[ "MetaCored" ].value = !uniforms[ "MetaCored" ].value;
    else if (key=="N") uniforms[ "outerCoresOff" ].value = !uniforms[ "outerCoresOff" ].value ;
    
    else if (key=="l"){zoomAtl41=!zoomAtl41; uniforms[ "free" ].value = !uniforms[ "free" ].value ;}
    else if (key=="L")window.zoom=1.;
    else if (key=="C")window.zoom=.00005;
    
    else if (key=="c")center=!center;
    else if (key=="v"){textON=!textON;}
    else if (key=="V"){        if (!onO)onO=true;
        
        RockInTheWater+=1;RockInTheWater=RockInTheWater%3;}
    
    else if (key=="z")uniforms[ "helm" ].value = !uniforms[ "helm" ].value;
    else if (key=="Z")uniforms[ "spokesVisualizeColors" ].value = !uniforms[ "spokesVisualizeColors" ].value;
    
    else if (key=="j"){
        if(uniforms[ "carousel" ].value==0)uniforms[ "carousel" ].value=-1.;
        else if(uniforms[ "carousel" ].value==-1.)uniforms[ "carousel" ].value=1.;
        else if(uniforms[ "carousel" ].value==1.)uniforms[ "carousel" ].value=0;
    }
    else if (key=="J")uniforms[ "onehundredfortyfourthousand" ].value=!uniforms[ "onehundredfortyfourthousand" ].value;
    
    else if (key=="k"){
        if(uniforms[ "metaCarousel" ].value==0)uniforms[ "metaCarousel" ].value=-1.;
        else if(uniforms[ "metaCarousel" ].value==-1.)uniforms[ "metaCarousel" ].value=1.;
        else if(uniforms[ "metaCarousel" ].value==1.)uniforms[ "metaCarousel" ].value=0;
    }
    else if (key=="K")uniforms.Inherited.value=!uniforms.Inherited.value;
    
    else if (key=="y") //uniforms[ "petals" ].value = 3.7082039325-6;//
        uniforms[ "petals" ].value -= 1.;
    else if (key=="Y"){
        window.blankBackground = !window.blankBackground;
        if(window.blankBackground)
            uniforms[ "colorCombo" ].value = 100;
        else
            uniforms[ "colorCombo" ].value = -1;
        
    }
    else if (key=="u") uniforms[ "petals" ].value += 1.;
    else if (key=="U") uniforms[ "Character" ].value = (uniforms[ "Character" ].value+1.)%12;

    else if (key=="?"){
        if(uniforms[ "spirated" ].value==0)uniforms[ "spirated" ].value=1;
        else if(uniforms[ "spirated" ].value==1)uniforms[ "spirated" ].value=-1;
        else if(uniforms[ "spirated" ].value==-1)uniforms[ "spirated" ].value=0;
    }
    
    else if (key=="|") {
        if(uniforms.chirality.value==3)uniforms.chirality.value=1;
        else if(uniforms.chirality.value==1)uniforms.chirality.value=-1;
        else if(uniforms.chirality.value==-1)uniforms.chirality.value=3;

    }
    else if (key=="{"){
        if(uniforms.eden.value!=4)uniforms.eden.value=(uniforms.eden.value+1)%3;
        else uniforms.eden.value=1;}
    else if (key=="}"){if(uniforms.eden.value==4)uniforms.eden.value=0;else uniforms.eden.value=4;}
    else if (key=="]"){zoomRate*=1.11111111;}
    else if (key=="["){zoomRate/=1.11111111;}
    else if (//event.keyCode==190||
             event.key==">") uniforms[ "metronome" ].value *= 1.1; //keycode for <
    else if ((//event.keyCode==188||
              event.key=="<")&&uniforms[ "metronome" ].value>1.) uniforms[ "metronome" ].value /= 1.1; //keycode for >
    
    else if (key=="i") zoomOutRatchetThreshold/= 1.12121;
    else if (key=="o") zoomOutRatchetThreshold*= 1.12121;
    else if (key=="O") window.starClover=!window.starClover;
    
    else if (key=="p"){
        framesLong=FPS;
        computeFPS=true;
    }
    else if (key=="P"){octaveStars=!octaveStars;
        /*
        if(!octaveStars)
        {
            scene.remove(starsANDwitnessesMesh)
        }
        else
        {
            scene.add(starsANDwitnessesMesh)
        }
         */
    }
    else if (key=="h"){
        fullscreen=!fullscreen
        if(fullscreen)openFullscreen();
        else closeFullscreen();
    }
    else if (key=="H")uniforms.cloverSlide.value=!uniforms.cloverSlide.value;
    else if (key==" ") resetAll();
    else if (key=="~")
    {
        onO=!onO;
    }
    else if (key=="w")window.volumeSpeed=!window.volumeSpeed;
    
    else if (key=="W"){
        //window.twist-=window.skew;
        if(window.twist-Math.floor(window.twist)>0.)window.twist=window.skew;
        window.twist+=2; window.twist = window.twist%24;
        //window.twist+=window.skew;

        if("osmd" in window&&osmd!=null)
        {
            osmd.Sheet.Transpose = twist/2.;
            osmd.updateGraphic();
            osmd.render();
        }
    }
    
    else if (key=="S"){

        if(window.twist-Math.floor(window.twist)>0.)window.twist=window.skew;
            
        window.twist-=2; window.twist = (window.twist+24)%24;

        if("osmd" in window&&osmd!=null)
        {
            osmd.Sheet.Transpose = twist/2.;
            osmd.updateGraphic();
            osmd.render();
        }
    }
    else if (key=="A"){window.flip = -1;uniforms.flipStar.value=-1.;}
    else if (key=="D"){window.flip = 1;uniforms.flipStar.value=1.;}

      else if (key=="R")   uniforms[ "remediatedColors" ].value=!uniforms[ "remediatedColors" ].value  ;


      else if (key=="="){window.movementRate *=1.11111111;  uniforms.rate.value*=1.11111111;}

      else if (key=="-"){window.movementRate /=1.11111111; uniforms.rate.value/=1.11111111;}

          else if (key=="e")uniforms.gameOn.value=!uniforms.gameOn.value;
          else if (key=="E")uniforms.MannyONtrail.value=uniforms.MannyONtrail.value=(1+uniforms.MannyONtrail.value)%3;

      if(uniforms.free.value) window.zoomCageSize=100000000000000000.;
      else window.zoomCageSize=1.5;
        
        number="no number";
    }


            //https://www.w3schools.com/howto/howto_js_fullscreen.asp
            var fullscreen=false;
            function openFullscreen() {
                
              if (document.documentElement.requestFullscreen) {
                  document.documentElement.requestFullscreen();
              } else if (document.documentElement.webkitRequestFullscreen) { /* Safari */
                  document.documentElement.webkitRequestFullscreen();
              } else if (document.body.msRequestFullscreen) { /* IE11 */
                  document.documentElement.msRequestFullscreen();
              }
            }

            function closeFullscreen() {
              if (document.exitFullscreen) {
                document.exitFullscreen();
              } else if (document.webkitExitFullscreen) { /* Safari */
                document.webkitExitFullscreen();
              } else if (document.msExitFullscreen) { /* IE11 */
                document.msExitFullscreen();
              }
            }

