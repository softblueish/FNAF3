#include "headers/game.hpp"

// Object stack
std::vector<Object*> animatedStack;

// Debug
const bool debug = false;
bool fastNights = false;
bool handyMan = false;
bool clearCameras = false;

// Engine variables
float deltaTime = 0;
float global_x_subpixel = 0;
float global_y_subpixel = 0;
float speed = 0.05;
int global_x = 0;
int global_y = 0;
const int maxGlobal_y = 0;
const int minGlobal_y = -976;
int gameMode = 3;

// Game variables
bool winCondition = false;
int night = 1;
int hour = 0;
int luresUsed = 0;
float cameraBlindness = 0;
float timePassedSinceNightStart = 0;
int blackoutTimer = 0;
int ventilationHealth = 0;
int lastVentilationHit = 0;
int lastVentilationPenaltyHit = 0;
float apathy = 0;
const int blackoutDelay = 2500;
const int requiredNormalRepair = 5;
const int requiredAllRepair = 10;
float cameraUsetime = 0;
float jumpscareLinger = 0;
float jumpscarePassiveness = 0;
unsigned int timeSinceLastPressedVentButton;
bool totalBlackout = false;
bool danger = false;

bool cameraOpen = false;
bool forceCameraOpen = false;
bool toolboxOpen = false;
int toolBoxHover = 0;
int camerasWithAnimations[] = {1, 4, 5, 6, 7};

// Player variables
int lookingAtRegularCamera = 1;
int lookingAtVentCamera = 0;
int sealedVent = 0;
int cameraBeingLured = 0;
bool lureActive = false;
bool ventSealed = false;
bool ventBeingSealed = false;
int ventSealingProgress = 0;
bool ventCameraOn = false;

// AI Levels
int AILevel;
float foxyChance = 0;

// Phantoms variables
bool balloonBoyOnCamera = false;
bool balloonBoyJumpscare = false;
bool balloonBoyFlashbang;
int balloonBoyForceSpawn = 0;
float balloonBoyPatience = 0;
bool foxyInOffice = false;
bool foxyJumpscare = false;
bool FoxyFlashbang = false;
bool isFreddyWalking = false;
int freddyCheck = 0;
int freddyJumpscareCheck = 0;
float freddyAnger = 0;
float freddyPosition = 0;
bool freddyJumpscareInit = false;

// Springtrap variables
int springtrapOnCamera = 7;
int springtrapOnVentCamera = 0;
bool springtrapInVents = true;
int springSkin = 0;
int aggressive = 0;
int springAI = 0;
int springTotalTurns = 0;
int movementCounter;
int lastSpringMoveCounter = 0;
bool hasSpringtrapSpawned = false;
std::vector<int> cameraSpringMovementIndex[10][2] = {
    {{-1}, {1}}, // Cam 1
    {{0}, {2, 4}}, // Cam 2
    {{1}, {3}}, // Cam 3
    {{2}, {4}}, // Cam 4
    {{3, 1}, {5, 7}}, // Cam 5
    {{4}, {6}}, // Cam 6
    {{5}, {7}}, // Cam 7
    {{6, 4}, {8}}, // Cam 8
    {{7}, {9}}, // Cam 9
    {{8}, {9}} // Cam 10

};

// Toolbox repairing and errors
bool cameraError = false;
bool cameraRepairing = false;
bool audioDeviceError = false;
bool audioRepairing = false;
bool ventilationError = false;
bool ventilationRepairing = false;
bool repairingAll = false;
int repairProgress = 0;

bool hasPhoneDudeSpoken = false;
bool hasAmbienceStarted = false;

// Win screen varaibles
float timeSinceWon = 0;
bool cheersPlayed = false;
float winScanLinesDelay = 1200;
int winScanLinesIndex = 0;

// Night start variables
float timeSinceNightStartScreenStart = 0;

// Special variables
int cameraButtonFramePositions[10][2] = {
    {624, 658},
    {828, 645},
    {927, 602},
    {927, 537},
    {768, 552},
    {624, 561},
    {624, 497},
    {727, 471},
    {794, 418},
    {903, 455}
};

// Load all assets to memory
Asset assetList[1150];
Mix_Chunk *soundList[70];

// Objects
Object officeBackground; // Office object
Object blackout; // Blackout object
Object officeBehindWindow; // Behind office window object
Object cameraOpenButton; // Camera open button
Object toolboxOpenButton; // Toolbox open button

Object rebootAudioDeviceButton; // Reboot audio device button
Object rebootCameraSystemButton; // Reboot camera system button
Object rebootVentilationButton; // Reboot ventilation button
Object rebootAllButton; // Reboot all button
Object exitToolboxButton; // Exit toolbox button

Object muteButton; // Mute button
Object cameraMonitor; // Camera monitor
Object toolboxMonitor; // Toolbox monitor
Object fan; // Fan object

// Text
Object nightText; // "NIGHT"
Object nightNumber; // Night number
Object AMText; // "AM"
Object firstHourNumber; // Hour number
Object secondHourNumber; // Hour number
Object sealCamTextInfo; // Seal cam text info

// Toolbox
Object toolBoxMainText; // Toolbox main text
Object toolBoxArrow; // Toolbox arrow
Object audioDeviceErrorToolBox; // Audio device error toolbox
Object cameraSystemErrorToolBox; // Camera system error toolbox
Object ventilationErrorToolBox; // Ventilation error toolbox
Object audioDeviceRepairingToolBox; // Audio device repairing toolbox
Object cameraSystemRepairingToolBox; // Camera system repairing toolbox
Object ventilationRepairingToolBox; // Ventilation repairing toolbox
Object allRepairingToolBox; // All repairing toolbox

// Cameras
Object cameras[10];
Object ventCameras[5];
Object springCameras[10][2];
Object ventSpringCameras[5];

// Camera elements
Object cameraMap; // Camera map
Object cameraStatic; // Camera static
Object cameraAudioDeviceErrorText;
Object cameraVideoErrorText;
Object cameraVentilationErrorText;
Object cameraButtonFrame[10];
Object cameraButtonFrameArrows[9];
Object cameraLargeButtonFrame[2];
Object cameraButtonLabels[10];
Object cameraGlitch;
Object cameraPlayAudioButton;
Object cameraToggleMap;
Object ventSealingAnimation;
Object cameraPlayAudioButtonTimeout;
Object lureObject;

// Phantoms
Object balloonBoyInCameraAsset;
Object balloonBoyJumpscareAsset;
Object foxyAsset;
Object freddyWalking;
Object freddyJumpscare;

// Camera vent elements
Object cameraMapVents; // Camera map vents
Object cameraVentButtonFrame[5];
Object cameraVentButtonLabels[5];
Object cameraVentButtonFrameArrows[5];
Object cameraVentBlocks[5];

// Invisible Objects
Object rightSideMouseHitbox; // Right side of the screen mouse hitbox
Object rightSideMouseHitboxSlow; // Right side of the screen mouse hitbox (Slow)
Object leftSideMouseHitbox; // Left side of the screen mouse hitbox
Object leftSideMouseHitboxSlow; // Left side of the screen mouse hitbox
Object freddysNose; // Freddy's nose, makes a little boop sound when clicked

// Win screen assets
Object fiveAMText; // "5:99 AM"
Object sixAMText; // "6:00 AM"
Object winFade; // Win screen fade
Object winScanLines[8];

// Night start assets
Object nightStartScanLines;
Object twelveamtext[6];

void setObjectSettings(); // Ignore this function, the real one is further down
void setDefaultValues(); // Ignore this function, the real one is further down
void gameplayRender(); // Ignore this function, the real one is further down

void initializeAssets(SDL_Window *window, SDL_Renderer *renderer, std::string path){
    // Load all assets to memory
    for(int i = 0; i < 1151; i++){
        std::string pathIterated = path + "/assets/" + std::to_string(i+1) + ".png";
        assetList[i] = Asset(pathIterated, renderer);
    }

    int soundCount = 0;
    for(const auto& entry : std::filesystem::directory_iterator(path + "/assets/audio/")){
        if(entry.is_regular_file() && entry.path().extension() == ".wav") {
            Mix_Chunk* sound = Mix_LoadWAV(entry.path().string().c_str());
            if(sound != nullptr) {
                soundList[soundCount] = sound;
                std::cout << "Loaded sound " << entry.path().string() << " (" << soundCount << ") \n";
            } else {
                std::cerr << "Failed to load sound " << entry.path().string() << ": " << Mix_GetError() << "\n";
            
            }
            soundCount++;
        }
    }

    std::cout << "3/4: Assets initialized\n";

    // Initialize objects (visuals)
    officeBackground = Object(&assetList[203], 0, 0, &global_x, &global_y, window, renderer);
    officeBackground.currentAnimation = new Animation();
    officeBackground.currentAnimation->addFrame(&assetList[203]);
    officeBackground.currentAnimation->addFrame(&assetList[204]);
    animatedStack.push_back(&officeBackground);
    officeBehindWindow = Object(&assetList[205], 0, 0, &global_x, &global_y, window, renderer);
    blackout = Object(&assetList[1149], 0, 0, &global_x, &global_y, window, renderer);

    // Text
    nightText = Object(&assetList[245], 20, 910, &global_x, &global_y, window, renderer);
    nightNumber = Object(&assetList[232], 18, 980, &global_x, &global_y, window, renderer);
    AMText = Object(&assetList[246], 46, 960, &global_x, &global_y, window, renderer);
    firstHourNumber = Object(&assetList[231], 42, 920, &global_x, &global_y, window, renderer);
    secondHourNumber = Object(&assetList[232], 42, 935, &global_x, &global_y, window, renderer);
    toolBoxMainText = Object(&assetList[599], 230, 120, &global_x, &global_y, window, renderer);
    toolBoxArrow = Object(&assetList[596], 360, 120, &global_x, &global_y, window, renderer);

    // Camera
    cameraMonitor = Object(&assetList[74], 90, 1980, &global_x, &global_y, window, renderer); // Camera monitor and animation
    cameraMonitor.currentAnimation = new Animation();
    cameraMonitor.currentSecondaryAnimation = new Animation();
    cameraMonitor.currentAnimation->addFrame(&assetList[74]);
    cameraMonitor.currentAnimation->addFrame(&assetList[72]);
    cameraMonitor.currentAnimation->addFrame(&assetList[71]);
    cameraMonitor.currentAnimation->addFrame(&assetList[69]);
    cameraMonitor.currentAnimation->addFrame(&assetList[68]);
    cameraMonitor.currentAnimation->addFrame(&assetList[63]);
    cameraMonitor.currentAnimation->addFrame(&assetList[62]);
    cameraMonitor.currentAnimation->addFrame(&assetList[61]);
    cameraMonitor.currentAnimation->addFrame(&assetList[60]);
    cameraMonitor.currentAnimation->addFrame(&assetList[59]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[59]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[60]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[61]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[62]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[63]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[68]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[69]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[71]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[72]);
    cameraMonitor.currentSecondaryAnimation->addFrame(&assetList[74]);
    animatedStack.push_back(&cameraMonitor);

    // Win screen elements
    fiveAMText = Object(&assetList[1129], 341, 348, &global_x, &global_y, window, renderer);
    sixAMText = Object(&assetList[1144], 341, 348, &global_x, &global_y, window, renderer);
    sixAMText.currentAnimation = new Animation();
    sixAMText.currentAnimation->addFrame(&assetList[1144]);
    sixAMText.currentAnimation->addFrame(&assetList[1145]);
    sixAMText.currentAnimation->addFrame(&assetList[1146]);
    sixAMText.currentAnimation->addFrame(&assetList[1147]);
    sixAMText.currentAnimation->addFrame(&assetList[1148]);
    animatedStack.push_back(&sixAMText);
    winFade = Object(&assetList[1149], 0, 0, &global_x, &global_y, window, renderer);
    for(int i = 0; i < 8; i++){
        winScanLines[i] = Object(&assetList[1136], 341, 0, &global_x, &global_y, window, renderer);
        winScanLines[i].currentAnimation = new Animation();
        winScanLines[i].currentAnimation->addFrame(&assetList[1135]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1136]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1134]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1133]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1131]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1127]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1131]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1133]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1134]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1136]);
        winScanLines[i].currentAnimation->addFrame(&assetList[1135]);
        animatedStack.push_back(&winScanLines[i]);
    }


    // Toolbox
    toolboxMonitor = Object(&assetList[744], 755, 50, &global_x, &global_y, window, renderer); // Toolbox monitor and animation
    toolboxMonitor.currentAnimation = new Animation();
    toolboxMonitor.currentSecondaryAnimation = new Animation();
    for(int i = 0; i < 11; i++){
        toolboxMonitor.currentAnimation->addFrame(&assetList[744-i]);
    }
    for(int i = 0; i < 11; i++){
        toolboxMonitor.currentSecondaryAnimation->addFrame(&assetList[734+i]);
    }
    animatedStack.push_back(&toolboxMonitor);

    // Fan
    fan = Object(&assetList[18], 288, 1150, &global_x, &global_y, window, renderer); // Fan object
    fan.currentAnimation = new Animation();
    for(int i = 0; i < 3; i++){
        fan.currentAnimation->addFrame(&assetList[18+i]);
    }
    animatedStack.push_back(&fan);

    // Camera elements
    sealCamTextInfo = Object(&assetList[1139], 345, 1520, &global_x, &global_y, window, renderer);

    // Camera static
    cameraStatic = Object(&assetList[39], 100, 1155, &global_x, &global_y, window, renderer);
    cameraStatic.currentAnimation = new Animation();
    cameraStatic.currentAnimation->addFrame(&assetList[39]);
    cameraStatic.currentAnimation->addFrame(&assetList[40]);
    cameraStatic.currentAnimation->addFrame(&assetList[41]);
    animatedStack.push_back(&cameraStatic);

    // Camera glitch
    cameraGlitch = Object(&assetList[151], 100, 1155, &global_x, &global_y, window, renderer);
    cameraGlitch.currentAnimation = new Animation();
    cameraGlitch.currentAnimation->addFrame(&assetList[151]);
    cameraGlitch.currentAnimation->addFrame(&assetList[152]);
    cameraGlitch.currentAnimation->addFrame(&assetList[153]);
    cameraGlitch.currentAnimation->addFrame(&assetList[154]);
    cameraGlitch.currentSecondaryAnimation = new Animation();
    cameraGlitch.currentSecondaryAnimation->addFrame(&assetList[150]);
    cameraGlitch.currentSecondaryAnimation->addFrame(&assetList[151]);
    cameraGlitch.currentSecondaryAnimation->addFrame(&assetList[152]);
    cameraGlitch.currentSecondaryAnimation->addFrame(&assetList[153]);
    animatedStack.push_back(&cameraGlitch);

    // Camera error elements
    cameraAudioDeviceErrorText = Object(&assetList[604], 150, 1200, &global_x, &global_y, window, renderer);
    cameraAudioDeviceErrorText.currentAnimation = new Animation();
    cameraAudioDeviceErrorText.currentAnimation->addFrame(&assetList[604]);
    cameraAudioDeviceErrorText.currentAnimation->addFrame(&assetList[1151]);
    animatedStack.push_back(&cameraAudioDeviceErrorText);
    cameraVideoErrorText = Object(&assetList[608], 200, 1200, &global_x, &global_y, window, renderer);
    cameraVideoErrorText.currentAnimation = new Animation();
    cameraVideoErrorText.currentAnimation->addFrame(&assetList[608]);
    cameraVideoErrorText.currentAnimation->addFrame(&assetList[1151]);
    animatedStack.push_back(&cameraVideoErrorText);
    cameraVentilationErrorText = Object(&assetList[610], 250, 1200, &global_x, &global_y, window, renderer);
    cameraVentilationErrorText.currentAnimation = new Animation();
    cameraVentilationErrorText.currentAnimation->addFrame(&assetList[610]);
    cameraVentilationErrorText.currentAnimation->addFrame(&assetList[1151]);
    animatedStack.push_back(&cameraVentilationErrorText);
    
    // Balloon boy
    balloonBoyInCameraAsset = Object(&assetList[70], 100, 1155, &global_x, &global_y, window, renderer);
    balloonBoyJumpscareAsset = Object(&assetList[226], 0, 0, &global_x, &global_y, window, renderer);
    balloonBoyJumpscareAsset.currentAnimation = new Animation();
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[226]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[317]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[328]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[338]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[341]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[342]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[343]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[345]);
    balloonBoyJumpscareAsset.currentAnimation->addFrame(&assetList[347]);
    animatedStack.push_back(&balloonBoyJumpscareAsset);

    // Foxy
    foxyAsset = Object(&assetList[184], 0, 330, &global_x, &global_y, window, renderer);
    foxyAsset.currentAnimation = new Animation();
    foxyAsset.currentAnimation->addFrame(&assetList[184]);
    foxyAsset.currentAnimation->addFrame(&assetList[183]);
    foxyAsset.currentAnimation->addFrame(&assetList[185]);
    foxyAsset.currentAnimation->addFrame(&assetList[186]);
    foxyAsset.currentAnimation->addFrame(&assetList[170]);
    foxyAsset.currentAnimation->addFrame(&assetList[174]);
    foxyAsset.currentAnimation->addFrame(&assetList[175]);
    foxyAsset.currentAnimation->addFrame(&assetList[176]);
    foxyAsset.currentAnimation->addFrame(&assetList[177]);
    foxyAsset.currentAnimation->addFrame(&assetList[178]);
    foxyAsset.currentAnimation->addFrame(&assetList[179]);
    foxyAsset.currentAnimation->addFrame(&assetList[180]);
    foxyAsset.currentAnimation->addFrame(&assetList[182]);
    animatedStack.push_back(&foxyAsset);

    // Freddy
    freddyWalking = Object(&assetList[641], 120, 1691, &global_x, &global_y, window, renderer);
    freddyWalking.currentAnimation = new Animation();
    freddyWalking.currentAnimation->addFrame(&assetList[641]);
    freddyWalking.currentAnimation->addFrame(&assetList[642]);
    freddyWalking.currentAnimation->addFrame(&assetList[643]);
    freddyWalking.currentAnimation->addFrame(&assetList[644]);
    freddyWalking.currentAnimation->addFrame(&assetList[645]);
    freddyWalking.currentAnimation->addFrame(&assetList[646]);
    freddyWalking.currentAnimation->addFrame(&assetList[647]);
    freddyWalking.currentAnimation->addFrame(&assetList[648]);
    freddyWalking.currentAnimation->addFrame(&assetList[649]);
    freddyWalking.currentAnimation->addFrame(&assetList[650]);
    freddyWalking.currentAnimation->addFrame(&assetList[651]);
    freddyWalking.currentAnimation->addFrame(&assetList[652]);
    freddyWalking.currentAnimation->addFrame(&assetList[653]);
    freddyWalking.currentAnimation->addFrame(&assetList[655]);
    freddyWalking.currentSecondaryAnimation = new Animation();
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[635]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[639]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[640]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[654]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[656]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[657]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[658]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[659]);
    freddyWalking.currentSecondaryAnimation->addFrame(&assetList[660]);
    animatedStack.push_back(&freddyWalking);

    freddyJumpscare = Object(&assetList[641], 0, 0, &global_x, &global_y, window, renderer);

    // Camera map
    cameraMap = Object(&assetList[532], 375, 1550, &global_x, &global_y, window, renderer);
    cameraMap.currentAnimation = new Animation();
    cameraMap.currentAnimation->addFrame(&assetList[532]);
    cameraMap.currentAnimation->addFrame(&assetList[574]);
    animatedStack.push_back(&cameraMap);
    cameraMapVents = Object(&assetList[626], 375, 1550, &global_x, &global_y, window, renderer);
    cameraMapVents.currentAnimation = new Animation();
    cameraMapVents.currentAnimation->addFrame(&assetList[626]);
    cameraMapVents.currentAnimation->addFrame(&assetList[627]);
    animatedStack.push_back(&cameraMapVents);

    // Camera button frames
    for(int i = 0; i < 10; i++){
        cameraButtonFrame[i] = Object(&assetList[81], cameraButtonFramePositions[i][1], cameraButtonFramePositions[i][0]+975, &global_x, &global_y, window, renderer);
    }

    for(int i = 0; i < 10; i++){
        cameraButtonLabels[i] = Object(&assetList[83+i], cameraButtonFramePositions[i][1]+8, cameraButtonFramePositions[i][0]+975+8, &global_x, &global_y, window, renderer);
    }

    // Camera arrows
    int cameraButtonFrameArrowPositions[9][3] = {
        {671, 1658-10, 0},
        {571, 1658-10, 0},
        {506, 1658-10, 0},
        {509-10, 1723, 1},
        {456-10, 1787, 1},
        {473, 1852, 2},
        {552, 1875, 2},
        {612, 1875, 2},
        {617, 1828, 3}
    };

    // Vent cameras
    ventCameras[0] = Object(&assetList[623], 100, 1155, &global_x, &global_y, window, renderer);
    ventCameras[1] = Object(&assetList[624], 100, 1155, &global_x, &global_y, window, renderer);
    ventCameras[2] = Object(&assetList[628], 100, 1155, &global_x, &global_y, window, renderer);
    ventCameras[3] = Object(&assetList[824], 100, 1155, &global_x, &global_y, window, renderer);
    ventCameras[4] = Object(&assetList[818], 100, 1155, &global_x, &global_y, window, renderer);

    // Springtrap vent cameras
    ventSpringCameras[0] = Object(&assetList[829], 100, 1155, &global_x, &global_y, window, renderer);
    ventSpringCameras[1] = Object(&assetList[831], 100, 1155, &global_x, &global_y, window, renderer);
    ventSpringCameras[2] = Object(&assetList[835], 100, 1155, &global_x, &global_y, window, renderer);
    ventSpringCameras[3] = Object(&assetList[841], 100, 1155, &global_x, &global_y, window, renderer);
    ventSpringCameras[4] = Object(&assetList[835], 100, 1155, &global_x, &global_y, window, renderer);

    // Camera vent button frames
    int cameraVentButtonFramePositions[5][2] = {
        {400, 1601},
        {521, 1666},
        {579, 1745},
        {499, 1835},
        {640, 1860}
    };

    for(int i = 0; i < 5; i++){
        cameraVentButtonFrame[i] = Object(&assetList[81], cameraVentButtonFramePositions[i][0], cameraVentButtonFramePositions[i][1], &global_x, &global_y, window, renderer);
    }

    cameraVentButtonLabels[0] = Object(&assetList[613], cameraVentButtonFramePositions[0][0]+8, cameraVentButtonFramePositions[0][1]+8, &global_x, &global_y, window, renderer);
    cameraVentButtonLabels[1] = Object(&assetList[614], cameraVentButtonFramePositions[1][0]+8, cameraVentButtonFramePositions[1][1]+8, &global_x, &global_y, window, renderer);
    cameraVentButtonLabels[2] = Object(&assetList[617], cameraVentButtonFramePositions[2][0]+8, cameraVentButtonFramePositions[2][1]+8, &global_x, &global_y, window, renderer);
    cameraVentButtonLabels[3] = Object(&assetList[619], cameraVentButtonFramePositions[3][0]+8, cameraVentButtonFramePositions[3][1]+8, &global_x, &global_y, window, renderer);
    cameraVentButtonLabels[4] = Object(&assetList[621], cameraVentButtonFramePositions[4][0]+8, cameraVentButtonFramePositions[4][1]+8, &global_x, &global_y, window, renderer);

    // Vent camera arrows
    int cameraVentButtonFrameArrowPositions[5][3] = {
        {422, 1623, 0},
        {531, 1641, 1},
        {592, 1731, 1},
        {651, 1843, 1},
        {509, 1876, 2}
    };

    for(int i = 0; i < 5; i++){
        switch(cameraVentButtonFrameArrowPositions[i][2]){
            case 0:
                cameraVentButtonFrameArrows[i] = Object(&assetList[96], cameraVentButtonFrameArrowPositions[i][0], cameraVentButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
            case 1:
                cameraVentButtonFrameArrows[i] = Object(&assetList[94], cameraVentButtonFrameArrowPositions[i][0], cameraVentButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
            case 2:
                cameraVentButtonFrameArrows[i] = Object(&assetList[93], cameraVentButtonFrameArrowPositions[i][0], cameraVentButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
            case 3:
                cameraVentButtonFrameArrows[i] = Object(&assetList[95], cameraVentButtonFrameArrowPositions[i][0], cameraVentButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
        }
    }

    for(int i = 0; i < 9; i++){
        switch(cameraButtonFrameArrowPositions[i][2]){
            case 0:
                cameraButtonFrameArrows[i] = Object(&assetList[93], cameraButtonFrameArrowPositions[i][0], cameraButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
            case 1:
                cameraButtonFrameArrows[i] = Object(&assetList[96], cameraButtonFrameArrowPositions[i][0], cameraButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
            case 2:
                cameraButtonFrameArrows[i] = Object(&assetList[94], cameraButtonFrameArrowPositions[i][0], cameraButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
            case 3:
                cameraButtonFrameArrows[i] = Object(&assetList[95], cameraButtonFrameArrowPositions[i][0], cameraButtonFrameArrowPositions[i][1], &global_x, &global_y, window, renderer);
                break;
        }
    }

    // Large camera buttons
    for(int i = 0; i < 2; i++){
        cameraLargeButtonFrame[i] = Object(&assetList[426], 560 + (i * 80), 1453, &global_x, &global_y, window, renderer);
    }
    cameraLargeButtonFrame[0].currentAnimation = new Animation();
    animatedStack.push_back(&cameraLargeButtonFrame[0]);
    cameraPlayAudioButton = Object(&assetList[366], 560+12, 1453+15, &global_x, &global_y, window, renderer);
    cameraToggleMap = Object(&assetList[431], 560+80+10, 1453+10, &global_x, &global_y, window, renderer);

    // Audio lure
    cameraPlayAudioButtonTimeout = Object(&assetList[533], 615, 1436, &global_x, &global_y, window, renderer);
    cameraPlayAudioButtonTimeout.currentAnimation = new Animation();
    cameraPlayAudioButtonTimeout.currentAnimation->addFrame(&assetList[533]);
    cameraPlayAudioButtonTimeout.currentAnimation->addFrame(&assetList[534]);
    cameraPlayAudioButtonTimeout.currentAnimation->addFrame(&assetList[535]);
    cameraPlayAudioButtonTimeout.currentAnimation->addFrame(&assetList[536]);
    cameraPlayAudioButtonTimeout.currentAnimation->addFrame(&assetList[537]);
    cameraPlayAudioButtonTimeout.currentAnimation->addFrame(&assetList[538]);
    animatedStack.push_back(&cameraPlayAudioButtonTimeout);
    lureObject = Object(&assetList[366], 560, 1453, &global_x, &global_y, window, renderer);
    lureObject.currentAnimation = new Animation();
    lureObject.currentAnimation->addFrame(&assetList[539]);
    lureObject.currentAnimation->addFrame(&assetList[540]);
    lureObject.currentAnimation->addFrame(&assetList[541]);
    lureObject.currentAnimation->addFrame(&assetList[542]);
    animatedStack.push_back(&lureObject);

    // Camera vent blocks
    int cameraVentBlockPositions[5][2] = {
        {473, 1586},
        {549, 1617},
        {599, 1708},
        {561, 1896},
        {675, 1819}
    };

    // Camera vent seal animation
    ventSealingAnimation = Object(&assetList[611], 710, 1810, &global_x, &global_y, window, renderer);
    ventSealingAnimation.currentAnimation = new Animation();
    ventSealingAnimation.currentAnimation->addFrame(&assetList[611]);
    ventSealingAnimation.currentAnimation->addFrame(&assetList[612]);
    ventSealingAnimation.currentAnimation->addFrame(&assetList[629]);
    ventSealingAnimation.currentAnimation->addFrame(&assetList[632]);
    ventSealingAnimation.currentAnimation->addFrame(&assetList[637]);
    animatedStack.push_back(&ventSealingAnimation);

    for(int i = 0; i < 5; i++){
        cameraVentBlocks[i] = Object(&assetList[531], cameraVentBlockPositions[i][0], cameraVentBlockPositions[i][1], &global_x, &global_y, window, renderer);
    }

    // Initialize objects (UI and buttons)
    cameraOpenButton = Object(&assetList[32], 120, 1880, &global_x, &global_y, window, renderer);
    toolboxOpenButton = Object(&assetList[77], 700, 280, &global_x, &global_y, window, renderer);
    muteButton = Object(&assetList[699], 10, 10, &global_x, &global_y, window, renderer);
    rebootAudioDeviceButton = Object(&assetList[544], 360, 205, &global_x, &global_y, window, renderer);
    rebootCameraSystemButton = Object(&assetList[545], 420, 205, &global_x, &global_y, window, renderer);
    rebootVentilationButton = Object(&assetList[555], 475, 205, &global_x, &global_y, window, renderer);
    rebootAllButton = Object(&assetList[594], 580, 205, &global_x, &global_y, window, renderer);
    exitToolboxButton = Object(&assetList[600], 630, 205, &global_x, &global_y, window, renderer);

    audioDeviceErrorToolBox = Object(&assetList[601], 365, 545, &global_x, &global_y, window, renderer);
    audioDeviceErrorToolBox.currentAnimation = new Animation();
    audioDeviceErrorToolBox.currentAnimation->addFrame(&assetList[601]);
    audioDeviceErrorToolBox.currentAnimation->addFrame(&assetList[603]);
    animatedStack.push_back(&audioDeviceErrorToolBox);

    cameraSystemErrorToolBox = Object(&assetList[601], 420, 545, &global_x, &global_y, window, renderer);
    cameraSystemErrorToolBox.currentAnimation = new Animation();
    cameraSystemErrorToolBox.currentAnimation->addFrame(&assetList[601]);
    cameraSystemErrorToolBox.currentAnimation->addFrame(&assetList[603]);
    animatedStack.push_back(&cameraSystemErrorToolBox);

    ventilationErrorToolBox = Object(&assetList[601], 480, 545, &global_x, &global_y, window, renderer);
    ventilationErrorToolBox.currentAnimation = new Animation();
    ventilationErrorToolBox.currentAnimation->addFrame(&assetList[601]);
    ventilationErrorToolBox.currentAnimation->addFrame(&assetList[603]);
    animatedStack.push_back(&ventilationErrorToolBox);

    // Repair animations
    audioDeviceRepairingToolBox = Object(&assetList[611], 360, 545, &global_x, &global_y, window, renderer);
    audioDeviceRepairingToolBox.currentAnimation = new Animation();
    audioDeviceRepairingToolBox.currentAnimation->addFrame(&assetList[611]);
    audioDeviceRepairingToolBox.currentAnimation->addFrame(&assetList[612]);
    audioDeviceRepairingToolBox.currentAnimation->addFrame(&assetList[629]);
    audioDeviceRepairingToolBox.currentAnimation->addFrame(&assetList[632]);
    audioDeviceRepairingToolBox.currentAnimation->addFrame(&assetList[637]);
    animatedStack.push_back(&audioDeviceRepairingToolBox);

    cameraSystemRepairingToolBox = Object(&assetList[611], 417, 545, &global_x, &global_y, window, renderer);
    cameraSystemRepairingToolBox.currentAnimation = new Animation();
    cameraSystemRepairingToolBox.currentAnimation->addFrame(&assetList[611]);
    cameraSystemRepairingToolBox.currentAnimation->addFrame(&assetList[612]);
    cameraSystemRepairingToolBox.currentAnimation->addFrame(&assetList[629]);
    cameraSystemRepairingToolBox.currentAnimation->addFrame(&assetList[632]);
    cameraSystemRepairingToolBox.currentAnimation->addFrame(&assetList[637]);
    animatedStack.push_back(&cameraSystemRepairingToolBox);

    ventilationRepairingToolBox = Object(&assetList[611], 475, 545, &global_x, &global_y, window, renderer);
    ventilationRepairingToolBox.currentAnimation = new Animation();
    ventilationRepairingToolBox.currentAnimation->addFrame(&assetList[611]);
    ventilationRepairingToolBox.currentAnimation->addFrame(&assetList[612]);
    ventilationRepairingToolBox.currentAnimation->addFrame(&assetList[629]);
    ventilationRepairingToolBox.currentAnimation->addFrame(&assetList[632]);
    ventilationRepairingToolBox.currentAnimation->addFrame(&assetList[637]);
    animatedStack.push_back(&ventilationRepairingToolBox);

    allRepairingToolBox = Object(&assetList[611], 580, 545, &global_x, &global_y, window, renderer);
    allRepairingToolBox.currentAnimation = new Animation();
    allRepairingToolBox.currentAnimation->addFrame(&assetList[611]);
    allRepairingToolBox.currentAnimation->addFrame(&assetList[612]);
    allRepairingToolBox.currentAnimation->addFrame(&assetList[629]);
    allRepairingToolBox.currentAnimation->addFrame(&assetList[632]);
    allRepairingToolBox.currentAnimation->addFrame(&assetList[637]);
    animatedStack.push_back(&allRepairingToolBox);

    // Night start elements
    nightStartScanLines = Object(&assetList[863], 0, 0, &global_x, &global_y, window, renderer);
    nightStartScanLines.currentAnimation = new Animation();
    nightStartScanLines.currentAnimation->addFrame(&assetList[863]);
    nightStartScanLines.currentAnimation->addFrame(&assetList[865]);
    nightStartScanLines.currentAnimation->addFrame(&assetList[866]);
    nightStartScanLines.currentAnimation->addFrame(&assetList[867]);
    nightStartScanLines.currentAnimation->addFrame(&assetList[868]);
    nightStartScanLines.currentAnimation->addFrame(&assetList[869]);
    nightStartScanLines.currentAnimation->addFrame(&assetList[871]);
    animatedStack.push_back(&nightStartScanLines);

    twelveamtext[0] = Object(&assetList[1098], 332, 411, &global_x, &global_y, window, renderer);
    twelveamtext[1] = Object(&assetList[837], 332, 411, &global_x, &global_y, window, renderer);
    twelveamtext[2] = Object(&assetList[838], 332, 411, &global_x, &global_y, window, renderer);
    twelveamtext[3] = Object(&assetList[842], 332, 411, &global_x, &global_y, window, renderer);
    twelveamtext[4] = Object(&assetList[843], 332, 411, &global_x, &global_y, window, renderer);
    twelveamtext[5] = Object(&assetList[844], 332, 411, &global_x, &global_y, window, renderer);


    // Initialize objects (invisible)
    rightSideMouseHitbox = Object(0, 896, &global_x, &global_y, 128, 768, window, renderer);
    rightSideMouseHitboxSlow = Object(0, 768, &global_x, &global_y, 128, 768, window, renderer);
    leftSideMouseHitbox = Object(0, -5, &global_x, &global_y, 128, 768+5, window, renderer);
    leftSideMouseHitboxSlow = Object(0, 128, &global_x, &global_y, 128, 768, window, renderer);
    freddysNose = Object(265, 662, &global_x, &global_y, 20, 20, window, renderer);

    std::cout << "4/4 Objects initialized (" << animatedStack.size() << " stacked)\n";

    // Prepare cameras
    cameras[0] = Object(&assetList[106], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[1] = Object(&assetList[97], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[1].currentAnimation = new Animation();
    cameras[1].currentAnimation->addFrame(&assetList[97]);
    cameras[1].currentAnimation->addFrame(&assetList[103]);
    animatedStack.push_back(&cameras[1]);
    cameras[2] = Object(&assetList[104], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[3] = Object(&assetList[105], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[4] = Object(&assetList[109], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[4].currentAnimation = new Animation();
    cameras[4].currentAnimation->addFrame(&assetList[109]);
    cameras[4].currentAnimation->addFrame(&assetList[110]);
    animatedStack.push_back(&cameras[4]);
    cameras[5] = Object(&assetList[98], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[5].currentAnimation = new Animation();
    cameras[5].currentAnimation->addFrame(&assetList[98]);
    cameras[5].currentAnimation->addFrame(&assetList[99]);
    animatedStack.push_back(&cameras[5]);
    cameras[6] = Object(&assetList[100], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[6].currentAnimation = new Animation();
    cameras[6].currentAnimation->addFrame(&assetList[100]);
    cameras[6].currentAnimation->addFrame(&assetList[101]);
    animatedStack.push_back(&cameras[6]);
    cameras[7] = Object(&assetList[112], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[7].currentAnimation = new Animation();
    cameras[7].currentAnimation->addFrame(&assetList[113]);
    cameras[7].currentAnimation->addFrame(&assetList[114]);
    animatedStack.push_back(&cameras[7]);
    cameras[8] = Object(&assetList[115], 100, 1155, &global_x, &global_y, window, renderer);
    cameras[9] = Object(&assetList[116], 100, 1155, &global_x, &global_y, window, renderer);

    springCameras[0][0] = Object(&assetList[295], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[0][1] = Object(&assetList[295], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[1][0] = Object(&assetList[132], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[1][0].currentAnimation = new Animation();
    springCameras[1][0].currentAnimation->addFrame(&assetList[132]);
    springCameras[1][0].currentAnimation->addFrame(&assetList[133]);
    animatedStack.push_back(&springCameras[1][0]);
    springCameras[1][1] = Object(&assetList[146], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[1][1].currentAnimation = new Animation();
    springCameras[1][1].currentAnimation->addFrame(&assetList[146]);
    springCameras[1][1].currentAnimation->addFrame(&assetList[147]);
    animatedStack.push_back(&springCameras[1][1]);
    springCameras[2][0] = Object(&assetList[111], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[2][1] = Object(&assetList[133], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[3][0] = Object(&assetList[122], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[3][1] = Object(&assetList[122], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[4][0] = Object(&assetList[119], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[4][0].currentAnimation = new Animation();
    springCameras[4][0].currentAnimation->addFrame(&assetList[119]);
    springCameras[4][0].currentAnimation->addFrame(&assetList[120]);
    animatedStack.push_back(&springCameras[4][0]);
    springCameras[4][1] = Object(&assetList[148], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[4][1].currentAnimation = new Animation();
    springCameras[4][1].currentAnimation->addFrame(&assetList[148]);
    springCameras[4][1].currentAnimation->addFrame(&assetList[149]);
    animatedStack.push_back(&springCameras[4][1]);
    springCameras[5][0] = Object(&assetList[117], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[5][0].currentAnimation = new Animation();
    springCameras[5][0].currentAnimation->addFrame(&assetList[117]);
    springCameras[5][0].currentAnimation->addFrame(&assetList[118]);
    animatedStack.push_back(&springCameras[5][0]);
    springCameras[5][1] = Object(&assetList[141], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[5][1].currentAnimation = new Animation();
    springCameras[5][1].currentAnimation->addFrame(&assetList[141]);
    springCameras[5][1].currentAnimation->addFrame(&assetList[142]);
    animatedStack.push_back(&springCameras[5][1]);
    springCameras[6][0] = Object(&assetList[124], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[6][0].currentAnimation = new Animation();
    springCameras[6][0].currentAnimation->addFrame(&assetList[124]);
    springCameras[6][0].currentAnimation->addFrame(&assetList[125]);
    springCameras[6][0].currentAnimation->addFrame(&assetList[126]);
    animatedStack.push_back(&springCameras[6][0]);
    springCameras[6][1] = Object(&assetList[187], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[6][1].currentAnimation = new Animation();
    springCameras[6][1].currentAnimation->addFrame(&assetList[187]);
    springCameras[6][1].currentAnimation->addFrame(&assetList[188]);
    springCameras[6][1].currentAnimation->addFrame(&assetList[189]);
    animatedStack.push_back(&springCameras[6][1]);
    springCameras[7][0] = Object(&assetList[127], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[7][0].currentAnimation = new Animation();
    springCameras[7][0].currentAnimation->addFrame(&assetList[127]);
    springCameras[7][0].currentAnimation->addFrame(&assetList[128]);
    springCameras[7][0].currentAnimation->addFrame(&assetList[129]);
    animatedStack.push_back(&springCameras[7][0]);
    springCameras[7][1] = Object(&assetList[136], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[7][1].currentAnimation = new Animation();
    springCameras[7][1].currentAnimation->addFrame(&assetList[136]);
    springCameras[7][1].currentAnimation->addFrame(&assetList[137]);
    springCameras[7][1].currentAnimation->addFrame(&assetList[138]);
    animatedStack.push_back(&springCameras[7][1]);
    springCameras[8][0] = Object(&assetList[130], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[8][1] = Object(&assetList[139], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[9][0] = Object(&assetList[131], 100, 1155, &global_x, &global_y, window, renderer);
    springCameras[9][1] = Object(&assetList[140], 100, 1155, &global_x, &global_y, window, renderer);

    setObjectSettings();
    setDefaultValues();
}

void setObjectSettings(){
    // Object settings
    officeBackground.setVisibility(true);
    officeBackground.forceShow = false;
    officeBehindWindow.setVisibility(true);
    officeBehindWindow.forceShow = false;

    cameraOpenButton.setVisibility(true);
    cameraOpenButton.opacity = 80;

    muteButton.setVisibility(true);
    muteButton.opacity = 40;
    muteButton.floating = true;

    for(int i = 0; i < 8; i++){
        winScanLines[i].floating = true;
    }

    for(int i = 0; i < 6; i++){
        twelveamtext[i].floating = true;
    }

    fiveAMText.floating = true;
    sixAMText.floating = true;

    nightStartScanLines.floating = true;

    toolboxOpenButton.setVisibility(true);
    toolboxOpenButton.opacity = 80;

    toolboxMonitor.reverseExpansion = true;
    cameraMonitor.reverseExpansion = true;

    // Jumpscares
    balloonBoyJumpscareAsset.floating = true;

    fan.setVisibility(true);

    // Animation speeds
    audioDeviceErrorToolBox.animationSpeed = 0.20;
    cameraSystemErrorToolBox.animationSpeed = 0.20;
    ventilationErrorToolBox.animationSpeed = 0.20;
    audioDeviceRepairingToolBox.animationSpeed = 0.08;
    cameraSystemRepairingToolBox.animationSpeed = 0.08;
    ventilationRepairingToolBox.animationSpeed = 0.08;
    allRepairingToolBox.animationSpeed = 0.08;
    officeBackground.animationSpeed = 0.05;
    cameraAudioDeviceErrorText.animationSpeed = 0.20;
    cameraVideoErrorText.animationSpeed = 0.20;
    cameraVentilationErrorText.animationSpeed = 0.20;
    cameraMap.animationSpeed = 0.02;
    cameraMapVents.animationSpeed = 0.02;
    ventSealingAnimation.animationSpeed = 0.08;
    lureObject.animationSpeed = 0.04;
    cameraPlayAudioButtonTimeout.animationSpeed = 0.01;
    balloonBoyJumpscareAsset.animationSpeed = 0.5;
    foxyAsset.animationSpeed = 0.5;
    freddyWalking.animationSpeed = 0.4;
    sixAMText.animationSpeed = 0.25;
    freddyWalking.animationSpeedSecondary = 0.4;

    // Text settings
    nightText.setVisibility(true);
    nightText.floating = true;
    nightNumber.setVisibility(true);
    nightNumber.floating = true;
    AMText.setVisibility(true);
    AMText.floating = true;
    firstHourNumber.setVisibility(true);
    firstHourNumber.floating = true;
    secondHourNumber.setVisibility(true);
    secondHourNumber.floating = true;
    toolBoxMainText.setVisibility(false);
    rebootAudioDeviceButton.setVisibility(false);
    rebootCameraSystemButton.setVisibility(false);
    rebootVentilationButton.setVisibility(false);
    rebootAllButton.setVisibility(false);
    exitToolboxButton.setVisibility(false);

    // Hitbox settings
    rightSideMouseHitbox.floating = true;
    rightSideMouseHitboxSlow.floating = true;
    leftSideMouseHitbox.floating = true;
    leftSideMouseHitboxSlow.floating = true;

    // Clickable objects
    cameraOpenButton.clickable = true;
    toolboxOpenButton.clickable = true;
    muteButton.clickable = true;

    freddysNose.clickable = true;

    // Bugfixes
    cameraGlitch.currentAnimation->isPlaying = true;
    cameraGlitch.currentSecondaryAnimation->isPlaying = true; 
    cameraMonitor.currentAnimation->isPlaying = false;
    ventSealingAnimation.currentAnimation->isPlaying = false;
}

void setDefaultValues() {
    // Default values
    cameraMonitor.setVisibility(false);
    toolboxMonitor.setVisibility(false);
    cameraStatic.setVisibility(false);
    cameraMap.setVisibility(false);
    cameraMapVents.setVisibility(false);
    cameraAudioDeviceErrorText.setVisibility(false);
    cameraVideoErrorText.setVisibility(false);
    cameraVentilationErrorText.setVisibility(false);
    audioDeviceErrorToolBox.setVisibility(false);
    cameraSystemErrorToolBox.setVisibility(false);
    ventilationErrorToolBox.setVisibility(false);
    audioDeviceRepairingToolBox.setVisibility(false);
    cameraSystemRepairingToolBox.setVisibility(false);
    ventilationRepairingToolBox.setVisibility(false);
    allRepairingToolBox.setVisibility(false);
    cameraPlayAudioButtonTimeout.currentAnimation->isPlaying = false;
    balloonBoyJumpscareAsset.currentAnimation->isPlaying = false;
    
    // Engine variables
    deltaTime = 0;
    global_x_subpixel = 0;
    global_y_subpixel = 0;
    speed = 0.05;
    global_x = 0;
    global_y = 0;

    // Game variables
    winCondition = false;
    luresUsed = 0;
    cameraBlindness = 0;
    timePassedSinceNightStart = 0;
    blackoutTimer = 0;
    ventilationHealth = 0;
    lastVentilationHit = 0;
    lastVentilationPenaltyHit = 0;
    apathy = 0;
    cameraUsetime = 0;
    jumpscareLinger = 0;
    jumpscarePassiveness = 0;
    timeSinceLastPressedVentButton;
    totalBlackout = false;
    danger = false;

    cameraOpen = false;
    forceCameraOpen = false;
    toolboxOpen = false;
    toolBoxHover = 0;

    // Player variables
    lookingAtRegularCamera = 1;
    lookingAtVentCamera = 0;
    sealedVent = 0;
    cameraBeingLured = 0;
    lureActive = false;
    ventSealed = false;
    ventBeingSealed = false;
    ventSealingProgress = 0;
    ventCameraOn = false;

    // AI Levels
    AILevel;
    foxyChance = 0;

    // Phantoms variables
    balloonBoyOnCamera = false;
    balloonBoyJumpscare = false;
    balloonBoyFlashbang;
    balloonBoyForceSpawn = 0;
    balloonBoyPatience = 0;
    foxyInOffice = false;
    foxyJumpscare = false;
    FoxyFlashbang = false;
    isFreddyWalking = false;
    freddyCheck = 0;
    freddyJumpscareCheck = 0;
    freddyAnger = 0;
    freddyPosition = 0;
    freddyJumpscareInit = false;

    // Springtrap variables
    springtrapOnCamera = 7;
    springtrapOnVentCamera = 0;
    springtrapInVents = false;
    springSkin = 0;
    int aggressive = 0;
    hasSpringtrapSpawned = false;

    // Toolbox repairing and errors
    cameraError = false;
    cameraRepairing = false;
    audioDeviceError = false;
    audioRepairing = false;
    ventilationError = false;
    ventilationRepairing = false;
    repairingAll = false;
    repairProgress = 0;

    hasPhoneDudeSpoken = false;
    hasAmbienceStarted = false;

    // Win screen varaibles
    timeSinceWon = 0;
    cheersPlayed = false;
    winScanLinesDelay = 1200;
    winScanLinesIndex = 0;

    // Night start variables
    timeSinceNightStartScreenStart = 0;

    // Night start variables
    timeSinceNightStartScreenStart = 0;

    for(int i = 0; i < 5; i++){
        cameraVentBlocks[i].currentAsset = &assetList[531];
        cameraVentBlocks[i].currentTexture = cameraVentBlocks[i].currentAsset->texture;
        cameraVentBlocks[i].width = cameraVentBlocks[i].currentAsset->width;
        cameraVentBlocks[i].height = cameraVentBlocks[i].currentAsset->height;
    }

}

void menuTick(){
    // Menu
}

void inGameTick(){
    // Advance night
    timePassedSinceNightStart += deltaTime;
    if(night != 1 && !fastNights) hour = (int)timePassedSinceNightStart / 60000; else {
        hour = (int)(timePassedSinceNightStart / 40000);
    }

    if(night != 1 && fastNights) hour = (int)timePassedSinceNightStart / 30000; else {
        if(fastNights) hour = (int)(timePassedSinceNightStart / 20000);
    }

    // Apathy penalty
    apathy += deltaTime;
    if(toolboxOpen||cameraOpen) {
        apathy = 0;
        lastVentilationPenaltyHit = 0;
    }

    // Hide springtrap if it's night 1
    if(night == 1) {
        springtrapInVents = false;
        springtrapOnCamera = -1;
        springtrapOnVentCamera = -1;
    }

    // Springtrap movement
    if(night != 1){
        if(springtrapOnCamera = -1) {
            // Springtrap is in office
        }
        if(timePassedSinceNightStart - lastSpringMoveCounter > 1000 && springtrapOnCamera != -1){
            movementCounter++;
            if(aggressive==1) movementCounter++;
            lastSpringMoveCounter = timePassedSinceNightStart;
            springAI = night;
            if(night == 6) springAI = 7;
            std::cout << "Movement counter: " << movementCounter << "\n";
            if(movementCounter > 10 - springAI - aggressive + rand() % 16 - springTotalTurns) {
                cameraGlitch.currentAnimation->isPlaying = true;
                movementCounter = 0;
                std::cout << "Movement check passed\n";
                int springDecision = rand() % (4 + aggressive);
                switch(springDecision){
                    case 0:
                        // Springtrap fails movement opportunity
                        std::cout << "Movement opportunity failed" << std::endl;
                        break;
                    case 1:
                        // Springtrap moves forward
                        springtrapOnCamera = cameraSpringMovementIndex[springtrapOnCamera][0][rand() % cameraSpringMovementIndex[springtrapOnCamera][0].size()];
                        springSkin = rand() % 2;
                        springTotalTurns = 0;
                        std::cout << "Springtrap moved forward to CAM " << springtrapOnCamera + 1 << " with springskin value " << springSkin << std::endl;
                        break;
                    case 2:
                        // Springtrap moves backwards
                        springtrapOnCamera = cameraSpringMovementIndex[springtrapOnCamera][1][rand() % cameraSpringMovementIndex[springtrapOnCamera][1].size()];
                        springSkin = rand() % 2;
                        springTotalTurns = 0;
                        std::cout << "Springtrap moved backwards to CAM" << springtrapOnCamera + 1 << " with springskin value " << springSkin << std::endl;
                        break;
                    case 4:
                        // Springtrap moves into vents (yet to be implemented)
                        std::cout << "Springtrap moved into vents" << std::endl;
                        break;
                    default:
                        std::cout << "Movement opportunity failed (Invalid Springtrap decision, " << springDecision << ")" << std::endl;
                        break;
                }
            }
        }
    }

    // Ventilation degradation
    switch(night){
        case 2:
            if(timePassedSinceNightStart - lastVentilationHit >12000) {
                ventilationHealth -= 1;
                lastVentilationHit = timePassedSinceNightStart;
            }
            break;
        case 3:
            if(timePassedSinceNightStart - lastVentilationHit >10000) {
                ventilationHealth -= 1;
                lastVentilationHit = timePassedSinceNightStart;
            }
            break;
        case 4:
            if(timePassedSinceNightStart - lastVentilationHit >9000) {
                ventilationHealth -= 1;
                lastVentilationHit = timePassedSinceNightStart;
            }
            break;
        case 5:
            if(timePassedSinceNightStart - lastVentilationHit >8000) {
                ventilationHealth -= 1;
                lastVentilationHit = timePassedSinceNightStart;
            }
            break;
        case 6:
            if(timePassedSinceNightStart - lastVentilationHit >6000) {
                ventilationHealth -= 1;
                lastVentilationHit = timePassedSinceNightStart;
            }
            break;
    }


    if(apathy > 10000 && night != 1 && apathy - lastVentilationPenaltyHit > 1000){
        ventilationHealth -= 1;
        lastVentilationPenaltyHit = apathy;
    }

    if(ventilationHealth <= -10) ventilationError = true;

    // Danger
    if(!danger&&(foxyInOffice||springtrapInVents)&&hasPhoneDudeSpoken){
        danger = true;
        Mix_PlayChannel(4, soundList[21], -1);
    } else {
        if(!(foxyInOffice||springtrapInVents)) {
            danger = false;
            Mix_HaltChannel(4);
        };
    }

    // Foxy chance
    switch(night){
        case 2:
            foxyChance = 1000;
            break;
        case 3:
            foxyChance = 50;
            break;
        case 4:
            foxyChance = 25;
            break;
        case 5:
            foxyChance = 10;
            break;
        case 6:
            foxyChance = 10;
            break;
        default:
            foxyChance = 0;
            break;
    }

    // Foxy jumpscare manager
    if(foxyInOffice){
        foxyAsset.setVisibility(true);
        foxyAsset.floating = false;
        foxyAsset.x = 0;
        foxyAsset.y = 320;
        if(!foxyJumpscare) {
            foxyAsset.currentAsset = &assetList[184];
            foxyAsset.currentTexture = foxyAsset.currentAsset->texture;
            foxyAsset.width = foxyAsset.currentAsset->width;
            foxyAsset.height = foxyAsset.currentAsset->height;
        }
        if(global_y * -1 <= 330){
            foxyJumpscare = true;
            foxyInOffice = false;
            foxyAsset.currentAnimation->isPlaying = true;
            Mix_PlayChannel(4, soundList[59], 0);
        }
    } else if(!foxyJumpscare && !FoxyFlashbang){
        foxyAsset.setVisibility(false);
    }

    if(foxyAsset.currentAnimation->isPlaying == false && foxyJumpscare){
        foxyJumpscare = false;
        FoxyFlashbang = true;
        foxyAsset.floating = true;
        foxyAsset.x = 0;
        foxyAsset.y = 0;
        jumpscareLinger = 3000;
        ventilationError = true;
    }

    if((int)timePassedSinceNightStart / 60000 > freddyCheck && night >= 3){
        if(rand() % 12 + 1 < night || hour == 4) isFreddyWalking = true;
        freddyCheck++;
    }

    if(isFreddyWalking){
        freddyWalking.setVisibility(true);
        freddyWalking.currentAnimation->isPlaying = true;
        if(global_y < -(freddyWalking.y - 1024) && !(cameraOpen || toolboxOpen)) {
            freddyAnger += deltaTime;
        }
        freddyWalking.y = 1691 - freddyPosition;
        freddyPosition += 0001 * speed * deltaTime;
        if(freddyWalking.y < 550) {
            isFreddyWalking = false;
            freddyPosition = 0;
            freddyAnger = 0;
        }
    }

    if(isFreddyWalking && freddyAnger > 3 * ((100 - (10 * night)) * 1000 ) / 60){
        freddyJumpscareInit = true;
        isFreddyWalking = false;
        freddyWalking.currentAnimation->isPlaying = false;
        freddyWalking.currentSecondaryAnimation->isPlaying = true;
    }

    if(freddyJumpscareInit && freddyWalking.currentSecondaryAnimation->isPlaying == false) {
        freddyWalking.setVisibility(false);
    }

    if(freddyJumpscareInit == true && freddyWalking.currentSecondaryAnimation->isPlaying == false){
        if(timeSinceNightStartScreenStart - freddyJumpscareCheck > 0) {
            freddyJumpscareCheck = timeSinceNightStartScreenStart;
            if(rand() % 2 == 0) {
                // This space is reserved for freddys jumpscare, it will run JUST ONCE when freddy is supposed to jumpscare the player

                // Reset
                freddyJumpscareInit = false;
            }
        }
    }

    // Night counter
    switch(night){
        case 1:
            nightNumber.currentAsset = &assetList[231];
            nightNumber.currentTexture = nightNumber.currentAsset->texture;
            nightNumber.width = nightNumber.currentAsset->width;
            nightNumber.height = nightNumber.currentAsset->height;
            break;
        case 2:
            nightNumber.currentAsset = &assetList[232];
            nightNumber.currentTexture = nightNumber.currentAsset->texture;
            nightNumber.width = nightNumber.currentAsset->width;
            nightNumber.height = nightNumber.currentAsset->height;
            break;
        case 3:
            nightNumber.currentAsset = &assetList[233];
            nightNumber.currentTexture = nightNumber.currentAsset->texture;
            nightNumber.width = nightNumber.currentAsset->width;
            nightNumber.height = nightNumber.currentAsset->height;
            break;
        case 4:
            nightNumber.currentAsset = &assetList[234];
            nightNumber.currentTexture = nightNumber.currentAsset->texture;
            nightNumber.width = nightNumber.currentAsset->width;
            nightNumber.height = nightNumber.currentAsset->height;
            break;
        case 5:
            nightNumber.currentAsset = &assetList[235];
            nightNumber.currentTexture = nightNumber.currentAsset->texture;
            nightNumber.width = nightNumber.currentAsset->width;
            nightNumber.height = nightNumber.currentAsset->height;
            break;
        case 6:
            nightNumber.currentAsset = &assetList[236];
            nightNumber.currentTexture = nightNumber.currentAsset->texture;
            nightNumber.width = nightNumber.currentAsset->width;
            nightNumber.height = nightNumber.currentAsset->height;
            break;
    }

    // Hour counter
    switch(hour){
        case 0:
            firstHourNumber.setVisibility(true);
            firstHourNumber.currentAsset = &assetList[231];
            firstHourNumber.currentTexture = firstHourNumber.currentAsset->texture;
            firstHourNumber.width = firstHourNumber.currentAsset->width;
            firstHourNumber.height = firstHourNumber.currentAsset->height;
            secondHourNumber.currentAsset = &assetList[232];
            secondHourNumber.currentTexture = secondHourNumber.currentAsset->texture;
            secondHourNumber.width = secondHourNumber.currentAsset->width;
            secondHourNumber.height = secondHourNumber.currentAsset->height;
            break;
        case 1:
            firstHourNumber.setVisibility(false);
            secondHourNumber.currentAsset = &assetList[231];
            secondHourNumber.currentTexture = secondHourNumber.currentAsset->texture;
            secondHourNumber.width = secondHourNumber.currentAsset->width;
            secondHourNumber.height = secondHourNumber.currentAsset->height;
            break;
        case 2:
            secondHourNumber.currentAsset = &assetList[232];
            secondHourNumber.currentTexture = secondHourNumber.currentAsset->texture;
            secondHourNumber.width = secondHourNumber.currentAsset->width;
            secondHourNumber.height = secondHourNumber.currentAsset->height;
            break;
        case 3:
            secondHourNumber.currentAsset = &assetList[233];
            secondHourNumber.currentTexture = secondHourNumber.currentAsset->texture;
            secondHourNumber.width = secondHourNumber.currentAsset->width;
            secondHourNumber.height = secondHourNumber.currentAsset->height;
            break;
        case 4:
            secondHourNumber.currentAsset = &assetList[234];
            secondHourNumber.currentTexture = secondHourNumber.currentAsset->texture;
            secondHourNumber.width = secondHourNumber.currentAsset->width;
            secondHourNumber.height = secondHourNumber.currentAsset->height;
            break;
        case 5:
            secondHourNumber.currentAsset = &assetList[235];
            secondHourNumber.currentTexture = secondHourNumber.currentAsset->texture;
            secondHourNumber.width = secondHourNumber.currentAsset->width;
            secondHourNumber.height = secondHourNumber.currentAsset->height;
            break;
    }

    // Phone dude
    if(!hasPhoneDudeSpoken){
        int nightList[6] = {1, 69, 6, 3, 51, 13};
        Mix_PlayChannel(1, soundList[nightList[night-1]], 0);
        hasPhoneDudeSpoken = true;
        muteButton.setVisibility(true);
        muteButton.clickable = true;
    }

    if(muteButton.isMouseClicking()){
        Mix_HaltChannel(1);
        muteButton.setVisibility(false);
        muteButton.clickable = false;
    }

    if(timePassedSinceNightStart >= 20000){
        muteButton.setVisibility(false);
        muteButton.clickable = false;
    }

    if(!hasAmbienceStarted){
        Mix_PlayChannel(2, soundList[44], -1);
        SDL_Delay(5);
        Mix_PlayChannel(3, soundList[38], -1);
        hasAmbienceStarted = true;
    }

    // Camera button only shown if player is looking to the right
        if(global_y < minGlobal_y + (10 * getScreenSize(0)/1024)) {
        cameraOpenButton.setVisibility(true); 
        cameraOpenButton.clickable = !ventBeingSealed;
    } else {
        cameraOpenButton.setVisibility(false);
        cameraOpenButton.clickable = false;
    }

    // Toolbox button only shown if player is looking to the left
    if(global_y > maxGlobal_y - (10 * getScreenSize(1)/1024) && !toolboxOpen) {
        toolboxOpenButton.setVisibility(true);
        toolboxOpenButton.clickable = true;
    } else {
        toolboxOpenButton.setVisibility(false);
        toolboxOpenButton.clickable = false;
    }

    // Office movement
    if(!cameraOpen&&!toolboxOpen&&!balloonBoyJumpscare&&!foxyJumpscare){
        if(rightSideMouseHitbox.isMouseHovering() && global_y - 1 > minGlobal_y) global_y_subpixel -= 25 * speed * deltaTime;
        if(rightSideMouseHitboxSlow.isMouseHovering() && global_y - 1 > minGlobal_y) global_y_subpixel -= 10 * speed * deltaTime;
        if(leftSideMouseHitbox.isMouseHovering() && global_y + 1 < maxGlobal_y) global_y_subpixel += 25 * speed * deltaTime;
        if(leftSideMouseHitboxSlow.isMouseHovering() && global_y + 1 < maxGlobal_y) global_y_subpixel += 10 * speed * deltaTime;
    }

    // Freddy nose boop
    if(freddysNose.isMouseClicking()){
        Mix_PlayChannel(4, soundList[65], 0);
    }

    // Toolbox monitor manager
    if(toolboxOpenButton.isMouseClicking()){
        if(!toolboxOpen){
            toolBoxHover = 0;
            Mix_PlayChannel(4, soundList[7], 0);
            toolboxOpen = true;
            toolboxOpenButton.setVisibility(false);
            toolboxMonitor.currentAnimation->isPlaying = true;
        } 
    }

    if(exitToolboxButton.isMouseClicking()){
        Mix_PlayChannel(4, soundList[25], 0);
        toolboxOpen = false;
        toolboxMonitor.currentSecondaryAnimation->isPlaying = true;
    }

    if(!toolboxOpen && !toolboxMonitor.currentSecondaryAnimation->isPlaying){ // Post animation manager when toolbox is closed
        toolboxMonitor.setVisibility(false);
    } else {
        toolboxMonitor.setVisibility(true);
    }

    // Toggle map
    if(cameraLargeButtonFrame[1].isMouseClicking()){
        Mix_PlayChannel(4, soundList[30], 0);
        ventCameraOn = !ventCameraOn;
        cameraGlitch.setVisibility(true);
        if(rand()%2 == 0){
            cameraGlitch.currentAnimation->isPlaying = true;
        } else {
            cameraGlitch.currentSecondaryAnimation->isPlaying = true;
        }
    }

    // AI manager
    if(night == 1) {
        AILevel = 0;
    } else if(night == 6){
        AILevel = 7;
    } else {
        AILevel = night;
    }

    // Repair managment
    if(rebootAudioDeviceButton.isMouseClicking() && !audioRepairing){
        audioRepairing = true;
    }

    if(rebootCameraSystemButton.isMouseClicking() && !cameraRepairing){
        cameraRepairing = true;
    }

    if(rebootVentilationButton.isMouseClicking() && !ventilationRepairing){
        ventilationRepairing = true;
    }

    if(rebootAllButton.isMouseClicking() && !repairingAll){
        repairingAll = true;
    }

    if(toolboxOpen == true && toolboxMonitor.currentAnimation->isPlaying == false){ // Post animation manager when toolbox is open
        toolBoxMainText.setVisibility(true);

        if(audioDeviceError && !audioRepairing){
            audioDeviceErrorToolBox.setVisibility(true);
        } else {
            audioDeviceErrorToolBox.setVisibility(false);
        }

        if(cameraError && !cameraRepairing){
            cameraSystemErrorToolBox.setVisibility(true);
        } else {
            cameraSystemErrorToolBox.setVisibility(false);
        }

        if(ventilationError && !ventilationRepairing){
            ventilationErrorToolBox.setVisibility(true);
        } else {
            ventilationErrorToolBox.setVisibility(false);
        }

        if(audioRepairing){
            audioDeviceRepairingToolBox.setVisibility(true);
        } else {
            audioDeviceRepairingToolBox.setVisibility(false);
        }

        if(cameraRepairing){
            cameraSystemRepairingToolBox.setVisibility(true);
        } else {
            cameraSystemRepairingToolBox.setVisibility(false);
        }

        if(ventilationRepairing){
            ventilationRepairingToolBox.setVisibility(true);
        } else {
            ventilationRepairingToolBox.setVisibility(false);
        }

        if(repairingAll){
            allRepairingToolBox.setVisibility(true);
        } else {
            allRepairingToolBox.setVisibility(false);
        }

        rebootAudioDeviceButton.setVisibility(true);
        rebootAudioDeviceButton.clickable = true;
        rebootCameraSystemButton.setVisibility(true);
        rebootCameraSystemButton.clickable = true;
        rebootVentilationButton.setVisibility(true);
        rebootVentilationButton.clickable = true;
        rebootAllButton.setVisibility(true);
        rebootAllButton.clickable = true;
        exitToolboxButton.setVisibility(true);
        exitToolboxButton.clickable = true;

        toolBoxArrow.setVisibility(true);
    } else {
        toolBoxMainText.setVisibility(false);

        audioDeviceErrorToolBox.setVisibility(false);
        cameraSystemErrorToolBox.setVisibility(false);
        ventilationErrorToolBox.setVisibility(false);
        audioDeviceRepairingToolBox.setVisibility(false);
        cameraSystemRepairingToolBox.setVisibility(false);
        ventilationRepairingToolBox.setVisibility(false);
        rebootAudioDeviceButton.setVisibility(false);
        rebootAudioDeviceButton.clickable = false;
        rebootCameraSystemButton.setVisibility(false);
        rebootCameraSystemButton.clickable = false;
        rebootVentilationButton.setVisibility(false);
        rebootVentilationButton.clickable = false;
        rebootAllButton.setVisibility(false);
        rebootAllButton.clickable = false;
        exitToolboxButton.setVisibility(false);
        exitToolboxButton.clickable = false;

        toolBoxArrow.setVisibility(false);
    }

    if(toolboxOpen==true && rebootAudioDeviceButton.isMouseHovering() && toolBoxHover != 0 && !(cameraRepairing || audioRepairing || ventilationRepairing || repairingAll)){
        toolBoxHover = 0;
        Mix_PlayChannel(4, soundList[30], 0);
    } else if(toolboxOpen==true && rebootCameraSystemButton.isMouseHovering() && toolBoxHover != 1 && !(cameraRepairing || audioRepairing || ventilationRepairing || repairingAll)){
        toolBoxHover = 1;
        Mix_PlayChannel(4, soundList[30], 0);
    } else if(toolboxOpen==true && rebootVentilationButton.isMouseHovering() && toolBoxHover != 2 && !(cameraRepairing || audioRepairing || ventilationRepairing || repairingAll)){
        toolBoxHover = 2;
        Mix_PlayChannel(4, soundList[30], 0);
    } else if(toolboxOpen==true && rebootAllButton.isMouseHovering() && toolBoxHover != 3 && !(cameraRepairing || audioRepairing || ventilationRepairing || repairingAll)){
        toolBoxHover = 3;
        Mix_PlayChannel(4, soundList[30], 0);
    } else if(toolboxOpen==true && exitToolboxButton.isMouseHovering() && toolBoxHover != 4 && !(cameraRepairing || audioRepairing || ventilationRepairing || repairingAll)){
        toolBoxHover = 4;
        Mix_PlayChannel(4, soundList[30], 0);
    }

    if(cameraRepairing || audioRepairing || ventilationRepairing || repairingAll){
        rebootAudioDeviceButton.clickable = false;
        rebootCameraSystemButton.clickable = false;
        rebootVentilationButton.clickable = false;
        rebootAllButton.clickable = false;
        exitToolboxButton.clickable = false;
    } else {
        rebootAudioDeviceButton.clickable = true;
        rebootCameraSystemButton.clickable = true;
        rebootVentilationButton.clickable = true;
        rebootAllButton.clickable = true;
        exitToolboxButton.clickable = true;
    }

    switch(toolBoxHover){
        case 0:
            toolBoxArrow.x = 360;
            break;
        case 1:
            toolBoxArrow.x = 420;
            break;
        case 2:
            toolBoxArrow.x = 475;
            break;
        case 3:
            toolBoxArrow.x = 580;
            break;  
        case 4:
            toolBoxArrow.x = 630;
            break;
    }

    // Blackout
    if(ventilationError == true){
        if(!blackout.isInvisible) blackoutTimer = -(blackoutDelay/2);
        blackout.setVisibility(true);
        totalBlackout = blackout.opacity > 95;
        blackoutTimer++;
        if(sin(((float)blackoutTimer)/blackoutDelay) > 0){
            blackout.opacity = 100 * sin((float)blackoutTimer/blackoutDelay);
        } else {
            blackout.opacity = 0;
        }
    } else {
        blackout.setVisibility(false);
        totalBlackout = false;
    }

    // Camera monitor manager
    if(cameraOpenButton.isMouseClicking() || (forceCameraOpen&&cameraOpen)){
        if(!cameraOpen){
            if(balloonBoyOnCamera) balloonBoyOnCamera = false;
            Mix_PlayChannel(0, soundList[37], -1);
            Mix_PlayChannel(4, soundList[28], 0);
            cameraOpen = true;
            cameraOpenButton.opacity = 30;
            cameraMonitor.currentAnimation->isPlaying = true;
        } else {
            if(((sin(rand()) + 1)/2)*1000 < 1000/foxyChance && foxyChance != 0){
            foxyInOffice = true;
            foxyAsset.opacity = 100;
            } else {
                foxyInOffice = false;
            }
            Mix_HaltChannel(0);
            Mix_PlayChannel(4, soundList[61], 0);
            cameraOpen = false;
            cameraOpenButton.opacity = 80;
            cameraMonitor.currentSecondaryAnimation->isPlaying = true;
        } 
    }

    if(!cameraOpen && !cameraMonitor.currentSecondaryAnimation->isPlaying){ // Post animation manager when camera is closed
        cameraMonitor.setVisibility(false);
    } else {
        cameraMonitor.setVisibility(true);
    }

    if(cameraOpen == true && cameraMonitor.currentAnimation->isPlaying == false){ // Post animation manager when camera is open
        cameraUsetime += deltaTime;
        Mix_Volume(0, (int)(128 * (((float)cameraStatic.opacity/100))));
        cameraStatic.setVisibility(!clearCameras);
        cameraLargeButtonFrame[1].clickable = !ventBeingSealed;
        if(audioDeviceError) cameraAudioDeviceErrorText.setVisibility(true);
        if(cameraError) cameraVideoErrorText.setVisibility(true);
        if(ventilationError) cameraVentilationErrorText.setVisibility(true);
        if(ventCameraOn != true){
            cameraLargeButtonFrame[0].clickable = !cameraPlayAudioButtonTimeout.currentAnimation->isPlaying && !audioDeviceError;
            cameraMap.setVisibility(true);
            cameraMapVents.setVisibility(false);
            sealCamTextInfo.setVisibility(false);
            for(int i = 0; i < 10; i++){
                cameras[i].setVisibility(true);
                springCameras[i][0].setVisibility(true);
                springCameras[i][1].setVisibility(true);
                cameraButtonFrame[i].setVisibility(true);
                cameraButtonLabels[i].setVisibility(true);
                cameraButtonFrame[i].clickable = true;
            }
            for(int i = 0; i < 5; i++){
                ventCameras[i].setVisibility(false);
                ventSpringCameras[i].setVisibility(false);
                cameraVentButtonFrame[i].setVisibility(false);
                cameraVentButtonLabels[i].setVisibility(false);
                cameraVentButtonFrame[i].clickable = false;
                cameraVentButtonFrameArrows[i].setVisibility(false);
                cameraVentBlocks[i].setVisibility(false);
            }
            for(int i = 0; i < 9; i++){
                cameraButtonFrameArrows[i].setVisibility(true);
            }
            cameraLargeButtonFrame[0].setVisibility(!cameraPlayAudioButtonTimeout.currentAnimation->isPlaying);
            cameraPlayAudioButton.setVisibility(!cameraPlayAudioButtonTimeout.currentAnimation->isPlaying);
            cameraPlayAudioButtonTimeout.setVisibility(cameraPlayAudioButtonTimeout.currentAnimation->isPlaying);
            lureObject.setVisibility(lureObject.currentAnimation->isPlaying);
            cameraLargeButtonFrame[1].setVisibility(true);
            cameraToggleMap.setVisibility(true);
        } else {
            for(int i = 0; i < 10; i++){
                cameras[i].setVisibility(false);
                springCameras[i][0].setVisibility(false);
                springCameras[i][1].setVisibility(false);
                cameraButtonFrame[i].setVisibility(false);
                cameraButtonLabels[i].setVisibility(false);
                cameraButtonFrame[i].clickable = false;
            }
            for(int i = 0; i < 5; i++){
                ventCameras[i].setVisibility(true);
                ventSpringCameras[i].setVisibility(true);
                cameraVentButtonFrame[i].setVisibility(true);
                cameraVentButtonLabels[i].setVisibility(true);
                cameraVentButtonFrame[i].clickable = !ventBeingSealed;
                cameraVentButtonFrameArrows[i].setVisibility(true);
                cameraVentBlocks[i].setVisibility(true);
            }
            for(int i = 0; i < 9; i++){
                cameraButtonFrameArrows[i].setVisibility(false);
            }
            cameraMapVents.setVisibility(true);
            cameraMap.setVisibility(false);
            sealCamTextInfo.setVisibility(true);
            cameraLargeButtonFrame[0].setVisibility(false);
            cameraPlayAudioButtonTimeout.setVisibility(false);
            lureObject.setVisibility(false);
            cameraPlayAudioButton.setVisibility(false);
            cameraLargeButtonFrame[1].setVisibility(true);
            cameraToggleMap.setVisibility(true);
            cameraLargeButtonFrame[0].clickable = false;
        }
    } else {
        cameraLargeButtonFrame[1].clickable = false;
        cameraLargeButtonFrame[0].clickable = false;
        cameraStatic.setVisibility(false);
        cameraAudioDeviceErrorText.setVisibility(false);
        cameraPlayAudioButtonTimeout.setVisibility(false);
        lureObject.setVisibility(false);
        sealCamTextInfo.setVisibility(false);
        cameraVideoErrorText.setVisibility(false);
        cameraVentilationErrorText.setVisibility(false);
        cameraMap.setVisibility(false);
        cameraMapVents.setVisibility(false);
        for(int i = 0; i < 10; i++){
            cameras[i].setVisibility(false);
            springCameras[i][0].setVisibility(false);
            springCameras[i][1].setVisibility(false);
            cameraButtonFrame[i].setVisibility(false);
            cameraButtonLabels[i].setVisibility(false);
            cameraButtonFrame[i].clickable = false;
        }
        for(int i = 0; i < 5; i++){
            ventCameras[i].setVisibility(false);
            ventSpringCameras[i].setVisibility(false);
            ventCameras[i].setVisibility(false);
            ventSpringCameras[i].setVisibility(false);
            cameraVentButtonFrame[i].setVisibility(false);
            cameraVentButtonLabels[i].setVisibility(false);
            cameraVentButtonFrame[i].clickable = false;
            cameraVentButtonFrameArrows[i].setVisibility(false);
            cameraVentBlocks[i].setVisibility(false);
        }
        for(int i = 0; i < 9; i++){
            cameraButtonFrameArrows[i].setVisibility(false);
        }
        cameraLargeButtonFrame[0].setVisibility(false);
        cameraPlayAudioButton.setVisibility(false);
        cameraLargeButtonFrame[1].setVisibility(false);
        cameraToggleMap.setVisibility(false);
    }

    // Audio lure
    if(cameraLargeButtonFrame[0].isMouseClicking() && !cameraPlayAudioButtonTimeout.currentAnimation->isPlaying){
        luresUsed++;
        lureActive = true;
        switch(rand()%3){
            case 0:
                Mix_PlayChannel(4, soundList[26], 0);
                break;
            case 1:
                Mix_PlayChannel(4, soundList[57], 0);
                break;
            case 2:
                Mix_PlayChannel(4, soundList[67], 0);
                break;
        }
        cameraPlayAudioButtonTimeout.currentAnimation->isPlaying = true;
        lureObject.currentAnimation->isPlaying = true;
        lureObject.x = cameraButtonFramePositions[lookingAtRegularCamera][1] - 24;
        lureObject.y = cameraButtonFramePositions[lookingAtRegularCamera][0] + 975 - 81;
    }

    // Punish player for using lure too much
    if(night != 1 && luresUsed > 6 - night && night != 6){
        audioDeviceError = true;
    } else if (night == 6 && luresUsed > 1){
        audioDeviceError = true;
    }

    if(!cameraPlayAudioButtonTimeout.currentAnimation->isPlaying) lureActive = false;

    // Camera button manager
    for(int i = 0; i < 10; i++) {
        if(i==lookingAtRegularCamera){
            cameraButtonFrame[i].currentAsset = &assetList[82];
            cameraButtonFrame[i].currentTexture = cameraButtonFrame[i].currentAsset->texture;
            cameraButtonFrame[i].width = cameraButtonFrame[i].currentAsset->width;
            cameraButtonFrame[i].height = cameraButtonFrame[i].currentAsset->height;
        } else {
            cameraButtonFrame[i].currentAsset = &assetList[81];
            cameraButtonFrame[i].currentTexture = cameraButtonFrame[i].currentAsset->texture;
            cameraButtonFrame[i].width = cameraButtonFrame[i].currentAsset->width;
            cameraButtonFrame[i].height = cameraButtonFrame[i].currentAsset->height;
        }
        if(cameraButtonFrame[i].isMouseClicking()){
            if(balloonBoyOnCamera) balloonBoyOnCamera = false;
            if(sin(rand()) + 1 < ((float)AILevel/(float)50) * 2 || balloonBoyForceSpawn == 1) {
                balloonBoyOnCamera = true;
                if(balloonBoyForceSpawn == 1) balloonBoyForceSpawn = 2;
                balloonBoyPatience = ((101 - (2 * AILevel)) * 1000)/60;

            }
            lookingAtRegularCamera = i;
            cameraGlitch.setVisibility(true);
            if(rand()%2 == 0){
                cameraGlitch.currentAnimation->isPlaying = true;
            } else {
                cameraGlitch.currentSecondaryAnimation->isPlaying = true;
            }
        }
    }

    // Vent camera button manager
    for(int i = 0; i < 5; i++) {
        if(i==lookingAtVentCamera){
            cameraVentButtonFrame[i].currentAsset = &assetList[82];
            cameraVentButtonFrame[i].currentTexture = cameraVentButtonFrame[i].currentAsset->texture;
            cameraVentButtonFrame[i].width = cameraVentButtonFrame[i].currentAsset->width;
            cameraVentButtonFrame[i].height = cameraVentButtonFrame[i].currentAsset->height;
        } else {
            cameraVentButtonFrame[i].currentAsset = &assetList[81];
            cameraVentButtonFrame[i].currentTexture = cameraVentButtonFrame[i].currentAsset->texture;
            cameraVentButtonFrame[i].width = cameraVentButtonFrame[i].currentAsset->width;
            cameraVentButtonFrame[i].height = cameraVentButtonFrame[i].currentAsset->height;
        }
        if(cameraVentButtonFrame[i].isMouseClicking()){
            if(timePassedSinceNightStart - timeSinceLastPressedVentButton < 200 && i == lookingAtVentCamera){
                sealedVent = i;
                ventSealed = false;
                ventSealingProgress = 0;
                ventBeingSealed = true;
                break;
            }
            lookingAtVentCamera = i;
            timeSinceLastPressedVentButton = timePassedSinceNightStart;
            cameraGlitch.setVisibility(true);
            if(rand()%2 == 0){
                cameraGlitch.currentAnimation->isPlaying = true;
            } else {
                cameraGlitch.currentSecondaryAnimation->isPlaying = true;
            }
        }
    }

    if(cameraGlitch.currentAnimation->isPlaying == false && cameraGlitch.currentSecondaryAnimation->isPlaying == false){
        cameraGlitch.setVisibility(false);
    }

    // Fan animation
    if(fan.currentAnimation->isPlaying != true){
        fan.currentAnimation->isPlaying = true;
    }

    // Error animations
    if(audioDeviceErrorToolBox.currentAnimation->isPlaying != true){
        audioDeviceErrorToolBox.currentAnimation->isPlaying = true;
    }

    if(cameraSystemErrorToolBox.currentAnimation->isPlaying != true){
        cameraSystemErrorToolBox.currentAnimation->isPlaying = true;
    }

    if(ventilationErrorToolBox.currentAnimation->isPlaying != true){
        ventilationErrorToolBox.currentAnimation->isPlaying = true;
    }

    // Camera error text
    if(cameraAudioDeviceErrorText.currentAnimation->isPlaying != true){
        cameraAudioDeviceErrorText.currentAnimation->isPlaying = true;
    }
    
    if(cameraVideoErrorText.currentAnimation->isPlaying != true){
        cameraVideoErrorText.currentAnimation->isPlaying = true;
    }

    if(cameraVentilationErrorText.currentAnimation->isPlaying != true){
        cameraVentilationErrorText.currentAnimation->isPlaying = true;
    }

    // Camera static/error causing
    if(night == 1){
        cameraStatic.opacity = 50 + 30 * sin(timePassedSinceNightStart) * sin(rand());
    } else if (night < 6){
        if(cameraUsetime < (60000 - (1200 * (night - 2))) && !cameraError){
            cameraStatic.opacity = 30 + (15 * sin(timePassedSinceNightStart) * sin(rand()))*(1 - (cameraUsetime/(60000 - (1200 * (night - 2))))) + 50 * (cameraUsetime/(60000 - (1200 * (night - 2))));
            if((int)(timePassedSinceNightStart/20)%500 == 0) cameraStatic.opacity = 100;
        } else {
            cameraError = true;
            cameraStatic.opacity = 100;
        }
    } else {
        if(cameraUsetime < 24000 && !cameraError){
            cameraStatic.opacity = 30 + (15 * sin(timePassedSinceNightStart) * sin(rand()))*(1 - (cameraUsetime/24000)) + 50 * (cameraUsetime/24000);
            if((int)(timePassedSinceNightStart/10)%500 == 0) cameraStatic.opacity = 100;
        } else {
            cameraError = true;
            cameraStatic.opacity = 100;
        }
    }
    if(cameraBlindness>0) {
        cameraBlindness -= deltaTime;
        if(cameraStatic.opacity < cameraBlindness / 2) cameraStatic.opacity = cameraBlindness / 2;
        if(cameraBlindness>200) cameraStatic.opacity = 100;
    }

    if(cameraGlitch.currentAnimation->isPlaying == true || cameraGlitch.currentSecondaryAnimation->isPlaying == true){
        cameraStatic.opacity = 100;
    }

    // Balloon boy
    if(balloonBoyForceSpawn == 0 && hour == 3) balloonBoyForceSpawn = 1;
    if(balloonBoyOnCamera && cameraError != true && cameraOpen && ventCameraOn != true){
        balloonBoyInCameraAsset.setVisibility(true);
        balloonBoyPatience -= deltaTime;
        if(balloonBoyPatience < 0){
            balloonBoyOnCamera = false;
            balloonBoyJumpscare = true;
        }
    } else {
        balloonBoyInCameraAsset.setVisibility(false);
    }

    if(balloonBoyJumpscare && balloonBoyJumpscareAsset.isInvisible != true){
        balloonBoyJumpscareAsset.currentAsset = &assetList[226];
        balloonBoyJumpscareAsset.currentTexture = balloonBoyJumpscareAsset.currentAsset->texture;
        balloonBoyJumpscareAsset.width = balloonBoyJumpscareAsset.currentAsset->width;
        balloonBoyJumpscareAsset.height = balloonBoyJumpscareAsset.currentAsset->height;
        forceCameraOpen = true;
        balloonBoyJumpscareAsset.setVisibility(true);
        balloonBoyJumpscareAsset.opacity = 100;
        jumpscarePassiveness = 500;
    }

    if(jumpscarePassiveness > 0) jumpscarePassiveness -= deltaTime;

    if(balloonBoyJumpscare && cameraMonitor.currentSecondaryAnimation->isPlaying == false && jumpscarePassiveness <= 0 && jumpscareLinger <= 0){
        Mix_PlayChannel(4, soundList[59], 0);
        ventilationError = true;
        balloonBoyJumpscareAsset.currentAnimation->isPlaying = true;
        balloonBoyFlashbang = true;
        jumpscareLinger = 2500;
        forceCameraOpen = false;
        cameraOpen = false;
    }

    // Jumpscare lingering
    if(jumpscareLinger > 0 && (balloonBoyFlashbang || FoxyFlashbang) && !balloonBoyJumpscareAsset.currentAnimation->isPlaying) {
        balloonBoyJumpscareAsset.opacity = jumpscareLinger / 2500 * 100;
        if(balloonBoyFlashbang) balloonBoyJumpscare = false;
        foxyAsset.opacity = jumpscareLinger / 3000 * 100;
        Mix_PlayChannel(-1, soundList[66], 0);
        jumpscareLinger -= deltaTime;
    }

    if((balloonBoyFlashbang || FoxyFlashbang) && jumpscareLinger <= 0){
        balloonBoyJumpscareAsset.setVisibility(false);
        foxyAsset.setVisibility(false);
        balloonBoyFlashbang = false;
        FoxyFlashbang = false;
    }

    // Static animation
    if(cameraStatic.currentAnimation->isPlaying != true){
        cameraStatic.currentAnimation->isPlaying = true;
    }

    if(cameraSystemRepairingToolBox.currentAnimation->isPlaying != true && cameraRepairing){
        cameraSystemRepairingToolBox.currentAnimation->isPlaying = true;
        repairProgress++;
        if(repairProgress != requiredNormalRepair) Mix_PlayChannel(4, soundList[27], 0);
    }

    // Repair animations
    if(audioDeviceRepairingToolBox.currentAnimation->isPlaying != true && audioRepairing){
        audioDeviceRepairingToolBox.currentAnimation->isPlaying = true;
        repairProgress++;
        if(repairProgress != requiredNormalRepair) Mix_PlayChannel(4, soundList[27], 0);
    }


    if(ventilationRepairingToolBox.currentAnimation->isPlaying != true && ventilationRepairing){
        ventilationRepairingToolBox.currentAnimation->isPlaying = true;
        repairProgress++;
        if(repairProgress != requiredNormalRepair) Mix_PlayChannel(4, soundList[27], 0);
    }

    if(allRepairingToolBox.currentAnimation->isPlaying != true && repairingAll){
        allRepairingToolBox.currentAnimation->isPlaying = true;
        repairProgress++;
        if(repairProgress != requiredAllRepair) Mix_PlayChannel(4, soundList[27], 0);
    }

    if(handyMan){
        apathy = 0;
        if(ventilationError) {
            ventilationError = false;
            ventilationHealth = 0;
            std::cout << "Ventilation broke, but don't worry, a handyman fixed the ventilation!" << std::endl;
        }
        if(audioDeviceError) {
            audioDeviceError = false;
            repairProgress = 0;
            luresUsed = 0;
            std::cout << "Audio device broke, but don't worry, a handyman fixed the audio device!" << std::endl;
        }
        if(cameraError) {
            cameraError = false;
            repairProgress = 0;
            cameraUsetime = 0;
            std::cout << "Camera system broke, but don't worry, a handyman fixed the camera system!" << std::endl;
        }
    }

    // Camera animations
    for(int i = 0; i < 5; i++){
        if(cameras[camerasWithAnimations[i]].currentAnimation->isPlaying != true){
            cameras[camerasWithAnimations[i]].currentAnimation->isPlaying = true;
        }
        if(springCameras[camerasWithAnimations[i]][0].currentAnimation->isPlaying != true){
            springCameras[camerasWithAnimations[i]][0].currentAnimation->isPlaying = true;
        }
        if(springCameras[camerasWithAnimations[i]][1].currentAnimation->isPlaying != true){
            springCameras[camerasWithAnimations[i]][1].currentAnimation->isPlaying = true;
        }
    }

    // Camera map animvation
    if(cameraMap.currentAnimation->isPlaying != true){
        cameraMap.currentAnimation->isPlaying = true;
    }

    if(cameraMapVents.currentAnimation->isPlaying != true){
        cameraMapVents.currentAnimation->isPlaying = true;
    }

    // Check if repair is done
    if(repairProgress >= requiredNormalRepair && audioRepairing){
        audioRepairing = false;
        audioDeviceError = false;
        repairProgress = 0;
        luresUsed = 0;
    }

    if(repairProgress >= requiredNormalRepair && cameraRepairing){
        cameraRepairing = false;
        cameraError = false;
        repairProgress = 0;
        cameraUsetime = 0;
    }

    if(repairProgress >= requiredNormalRepair && ventilationRepairing){
        ventilationRepairing = false;
        ventilationError = false;
        ventilationHealth = 0;
        repairProgress = 0;
        blackoutTimer = 0;
    }

    if(repairProgress >= requiredAllRepair && repairingAll){
        repairingAll = false;
        audioDeviceError = false;
        cameraError = false;
        ventilationError = false;
        ventilationHealth = 0;
        repairProgress = 0;
        luresUsed = 0;
        blackoutTimer = 0;
        cameraUsetime = 0;
    }

    // Alarm animation and sound
    if((ventilationError)){
        if(!officeBackground.currentAnimation->isPlaying){
            officeBackground.currentAnimation->isPlaying = true;
            Mix_PlayChannel(5, soundList[2], 0);
        }
    } else {
        Mix_HaltChannel(5);
        officeBackground.currentAnimation->isPlaying = false;
        officeBackground.currentAsset = &assetList[203];
        officeBackground.currentTexture = officeBackground.currentAsset->texture;
        officeBackground.width = officeBackground.currentAsset->width;
        officeBackground.height = officeBackground.currentAsset->height;
    }

    // Seal vents if need be
    if(ventBeingSealed){
        sealCamTextInfo.currentAsset = &assetList[1140];
        sealCamTextInfo.currentTexture = sealCamTextInfo.currentAsset->texture;
        sealCamTextInfo.width = sealCamTextInfo.currentAsset->width;
        sealCamTextInfo.height = sealCamTextInfo.currentAsset->height;
        ventSealingAnimation.setVisibility(ventCameraOn);
        cameraOpenButton.clickable = false;
        if(ventSealingProgress == 3){
            ventSealed = true;
            ventBeingSealed = false;
            cameraOpenButton.clickable = true;
            Mix_PlayChannel(4, soundList[31], 0);
            sealCamTextInfo.currentAsset = &assetList[1139];
            sealCamTextInfo.currentTexture = sealCamTextInfo.currentAsset->texture;
            sealCamTextInfo.width = sealCamTextInfo.currentAsset->width;
            sealCamTextInfo.height = sealCamTextInfo.currentAsset->height;
            for(int i = 0; i < 5; i++){
                if(i == sealedVent){
                    cameraVentBlocks[sealedVent].currentAsset = &assetList[609];
                    cameraVentBlocks[sealedVent].currentTexture = cameraVentBlocks[sealedVent].currentAsset->texture;
                    cameraVentBlocks[sealedVent].width = cameraVentBlocks[sealedVent].currentAsset->width;
                    cameraVentBlocks[sealedVent].height = cameraVentBlocks[sealedVent].currentAsset->height;
                } else {
                    cameraVentBlocks[i].currentAsset = &assetList[531];
                    cameraVentBlocks[i].currentTexture = cameraVentBlocks[i].currentAsset->texture;
                    cameraVentBlocks[i].width = cameraVentBlocks[i].currentAsset->width;
                    cameraVentBlocks[i].height = cameraVentBlocks[i].currentAsset->height;
                }
            }
        }
        if(ventSealingAnimation.currentAnimation->isPlaying == false){
            ventSealingAnimation.currentAnimation->isPlaying = true;
            ventSealingProgress++;
            Mix_PlayChannel(4, soundList[27], 0);
        }
    } else {
        ventSealingAnimation.setVisibility(false);
    }

    // Update global subpixel variables
    global_x = (int)global_x_subpixel;
    global_y = (int)global_y_subpixel;

    if(hour == 6) {
        winCondition = true;
    }

    if(winCondition == true) {
        gameMode = 2;
        timeSinceWon = 0;
        for(int i = 0; i < 6; i++){
            Mix_HaltChannel(i);
        }
        Mix_PlayChannel(4, soundList[62], 0);
    }

    gameplayRender();
}

void gameplayRender(){
    // Background
    officeBehindWindow.render();

    // Behind window phantoms/Springtrap
    freddyWalking.render();

    // Scenery
    officeBackground.render();
    fan.render();

    // Jumpscares
    if(!balloonBoyFlashbang) balloonBoyJumpscareAsset.render();
    if(foxyInOffice) foxyAsset.render();

    toolboxMonitor.render();
    cameraMonitor.render();

    // Toolbox
    toolBoxMainText.render();
    rebootAudioDeviceButton.render();
    rebootCameraSystemButton.render();
    rebootVentilationButton.render();
    rebootAllButton.render();
    exitToolboxButton.render();
    toolBoxArrow.render();
    audioDeviceErrorToolBox.render();
    cameraSystemErrorToolBox.render();
    ventilationErrorToolBox.render();
    audioDeviceRepairingToolBox.render();
    cameraSystemRepairingToolBox.render();
    ventilationRepairingToolBox.render();
    allRepairingToolBox.render();

    // Camera
    if(springtrapInVents == false && springtrapOnCamera == lookingAtRegularCamera){
        springCameras[lookingAtRegularCamera][springSkin].render();
    } else {
        cameras[lookingAtRegularCamera].render();
    }
    balloonBoyInCameraAsset.render();

    if(springtrapInVents == true && springtrapOnVentCamera == lookingAtVentCamera){
        ventSpringCameras[lookingAtVentCamera].render();
    } else {
        ventCameras[lookingAtVentCamera].render();
    }

    cameraStatic.render();
    cameraGlitch.render();
    cameraVideoErrorText.render();
    cameraAudioDeviceErrorText.render();
    cameraVentilationErrorText.render();
    cameraMap.render();
    cameraMapVents.render();
    for(int i = 0; i < 9; i++){
        cameraButtonFrameArrows[i].render();
    }
    for(int i = 0; i < 10; i++){
        cameraButtonFrame[i].render();
        cameraButtonLabels[i].render();
    }
    for(int i = 0; i < 5; i++){
        cameraVentButtonFrameArrows[i].render();
        cameraVentBlocks[i].render();
    }
    for(int i = 0; i < 5; i++){
        cameraVentButtonFrame[i].render();
        cameraVentButtonLabels[i].render();
    }
    cameraLargeButtonFrame[0].render();
    cameraPlayAudioButton.render();
    cameraLargeButtonFrame[1].render();
    cameraToggleMap.render();
    sealCamTextInfo.render();
    ventSealingAnimation.render();
    lureObject.render();
    cameraPlayAudioButtonTimeout.render();

    // General buttons
    if(!balloonBoyJumpscareAsset.currentAnimation->isPlaying) cameraOpenButton.render();
    toolboxOpenButton.render();
    muteButton.render();

    // Text
    nightText.render();
    nightNumber.render();
    AMText.render();
    firstHourNumber.render();
    secondHourNumber.render();

    // Flashbang
    if(balloonBoyFlashbang) balloonBoyJumpscareAsset.render();
    if(foxyJumpscare||FoxyFlashbang) foxyAsset.render();

    // Blackout
    blackout.render();
}

void winScreenTick(){
    if(timeSinceWon == 0) {
        Mix_PlayChannel(4, soundList[5], 0);
        cheersPlayed = false;
        winScanLinesIndex = 0;  
    }

    timeSinceWon += deltaTime;
    winScanLinesDelay -= deltaTime;

    if(winScanLinesDelay < 0 && winScanLinesIndex < 8){
        winScanLines[winScanLinesIndex].setVisibility(true);
        winScanLines[winScanLinesIndex].animationSpeed = 0.08;
        winScanLines[winScanLinesIndex].currentAnimation->isPlaying = true;
        winScanLines[winScanLinesIndex].x = 380 + (rand() % 200 - 100);
        winScanLinesIndex++;
        winScanLinesDelay = rand() % 300 + 200;for(int i = 0; i < 8; i++);
    }

    for (int i = 0; i < 8; i++){
        if(winScanLines[i].currentAnimation->isPlaying == false){
            winScanLines[i].setVisibility(false);
        }
    }

    if(timeSinceWon < 1000) {
        gameplayRender();
        winFade.setVisibility(true);
        winFade.opacity = timeSinceWon/1000 * 100;
        fiveAMText.opacity = timeSinceWon/1000 * 100;
        sixAMText.opacity = timeSinceWon/1000 * 100;
    }

    if(timeSinceWon < 4000){
        fiveAMText.setVisibility(true);
        sixAMText.setVisibility(false);
    }

    if(timeSinceWon > 4000){
        if(cheersPlayed == false){
            Mix_PlayChannel(5, soundList[14], 0);
            cheersPlayed = true;
        }
        fiveAMText.setVisibility(false);
        sixAMText.setVisibility(true);
        if(sixAMText.currentAnimation->isPlaying != true){
            sixAMText.currentAnimation->isPlaying = true;
        }
    }

    if(timeSinceWon > 12000){
        night++;
        gameMode = 3;
        setDefaultValues();
        return;
    }

    winFade.render();
    for(int i = 0; i < 8; i++){
        winScanLines[i].render();
    }
    fiveAMText.render();
    sixAMText.render();
}

void nightStartTick(){
    if(timeSinceNightStartScreenStart == 0) {
        Mix_PlayChannel(4, soundList[39], 0);
        nightStartScanLines.setVisibility(true);
        nightStartScanLines.animationSpeed = 0.80;
        nightStartScanLines.opacity = 80;
        nightStartScanLines.currentAnimation->isPlaying = true;
    }
    if(nightStartScanLines.currentAnimation->isPlaying == false) nightStartScanLines.setVisibility(false);
    for(int i = 0; i < 6; i++) twelveamtext[i].setVisibility(i==night-1);
    timeSinceNightStartScreenStart += deltaTime;
    if(timeSinceNightStartScreenStart > 4800){
        gameMode = 1;
        timeSinceNightStartScreenStart = 0;
        return;
    }
    twelveamtext[night-1].render();
    nightStartScanLines.render();
}

void tick(float delta, SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event){
    if(debug){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        std::cout << mouseY - global_x << " " << mouseX - global_y << std::endl;
    }
    deltaTime = delta;

    // If the key c, d and + are pressed at the same time, use keyboard get state
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_C] && state[SDL_SCANCODE_D] && state[SDL_SCANCODE_MINUS] && gameMode == 1){
        winCondition = true;
        std::cout << "Skipped night " << night << std::endl;
    }


    // Play animations, if any
    for(int i = 0; i < animatedStack.size(); i++){
        if(animatedStack[i]->currentAnimation != NULL){
            if(animatedStack[i]->currentAnimation->isPlaying == true){
                animatedStack[i]->currentAsset = animatedStack[i]->currentAnimation->frames[animatedStack[i]->currentAnimation->currentFrame];
                animatedStack[i]->currentTexture = animatedStack[i]->currentAsset->texture;
                if(animatedStack[i]->reverseExpansion==true){
                    animatedStack[i]->x += animatedStack[i]->height - animatedStack[i]->currentAsset->height;
                    animatedStack[i]->y += animatedStack[i]->width - animatedStack[i]->currentAsset->width;
                }
                animatedStack[i]->width = animatedStack[i]->currentAsset->width;
                animatedStack[i]->height = animatedStack[i]->currentAsset->height;
                animatedStack[i]->currentAnimation->currentSubFrame += speed * deltaTime * animatedStack[i]->animationSpeed;
                animatedStack[i]->currentAnimation->currentFrame = (int)animatedStack[i]->currentAnimation->currentSubFrame;
                if(animatedStack[i]->currentAnimation->currentFrame >= animatedStack[i]->currentAnimation->frames.size()){
                    animatedStack[i]->currentAnimation->currentFrame = 0;
                    animatedStack[i]->currentAnimation->currentSubFrame = 0;
                    animatedStack[i]->currentAnimation->isPlaying = false;
                }
            }
        }
        if(animatedStack[i]->currentSecondaryAnimation != NULL){
            if(animatedStack[i]->currentSecondaryAnimation->isPlaying == true){
                animatedStack[i]->currentAsset = animatedStack[i]->currentSecondaryAnimation->frames[animatedStack[i]->currentSecondaryAnimation->currentFrame];
                animatedStack[i]->currentTexture = animatedStack[i]->currentAsset->texture;
                if(animatedStack[i]->reverseExpansion==true){
                    animatedStack[i]->x += animatedStack[i]->height - animatedStack[i]->currentAsset->height;
                    animatedStack[i]->y += animatedStack[i]->width - animatedStack[i]->currentAsset->width;
                }
                animatedStack[i]->width = animatedStack[i]->currentAsset->width;
                animatedStack[i]->height = animatedStack[i]->currentAsset->height;
                animatedStack[i]->currentSecondaryAnimation->currentSubFrame += speed * deltaTime * animatedStack[i]->animationSpeedSecondary;
                animatedStack[i]->currentSecondaryAnimation->currentFrame = (int)animatedStack[i]->currentSecondaryAnimation->currentSubFrame;
                if(animatedStack[i]->currentSecondaryAnimation->currentFrame >= animatedStack[i]->currentSecondaryAnimation->frames.size()){
                    animatedStack[i]->currentSecondaryAnimation->currentFrame = 0;
                    animatedStack[i]->currentSecondaryAnimation->currentSubFrame = 0;
                    animatedStack[i]->currentSecondaryAnimation->isPlaying = false;
                }
            }
        }  
    }

    switch(gameMode){
        case 0: // Menu
            menuTick();
            break;
        case 1: // Gameplay
            inGameTick();
            break;
        case 2: // Night end
            winScreenTick();
            break;
        case 3: // Night start
            nightStartTick();
            break;
    }
}