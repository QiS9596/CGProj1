#include "coordinatecalculator.h"
int mywait = 0;
CoordinateCalculator::CoordinateCalculator()
{
    initDefaultCoordinates();
    state = STANDBY_STATE;
}

void CoordinateCalculator::updateDynamicCoordinate(){
    switch(state){
    case STANDBY_STATE:
        standby();
        break;
    case MOVE_HAND_STATE:
        moveHand();
        break;
    case YES_POSE_STATE:
//        temp = 0;
        yesPose();
        break;
    case RUNING_STATE:
        runing();
        break;
    case WALK_STATE:
        walk();
        break;
    case 5:
        angry();
        break;
    case TEST:
        test();
        break;
    case SUMMON_SWORD_STATE:
        summonSword();
        break;
    case TRANSFORMATION_STATE:
        transformation();
        break;

    default:
        standby();
    }
}
void CoordinateCalculator::standby(){
    /* stand by function is used to set all of
     * the dynamic variables to zero/one
     * the translate and rotate variables will be
     * set to 0, whereas the scale variable will be
     * set to 1.
     * NOTE that, ideally, after using standby()
     * function, our robot should be stand there
     */

    /* The following for loop will set translate
     * variables to 0, and set scale variables to 1
     */
    for(int index = 0; index < 3; index++){
        ph_dynamic_translate[index] = 0;
    //==================
        /*neck*/
        neck_dynamic_translate[index] = 0;
        neck_dynamic_scale[index] = 1;
    //=====================================
        /*body*/
        body_dynamic_translate[index] = 0;
        body_dynamic_scale[index] = 1;
    //=====================================
        /*left shoulder*/
        leftshoulder_dynamic_translate[index] = 0;
        leftshoulder_dynamic_scale[index] = 1;
    //=====================================
        /*right shoulder*/
        rightshoulder_dynamic_translate[index] = 0;
        rightshoulder_dynamic_scale[index] = 1;
    //=====================================
        /*left wing*/
        leftwing_dynamic_translate[index] = 0;
        leftwing_dynamic_scale[index] = 1;
    //=====================================
        /*ring wing*/
        rightwing_dynamic_translate[index] = 0;
        rightwing_dynamic_scale[index] = 1;
    //=====================================
        /*left arm*/
        leftarm_dynamic_translate[index] = 0;
        leftarm_dynamic_scale[index] = 1;
    //=====================================
        /*right arm*/
        rightarm_dynamic_translate[index] = 0;
        rightarm_dynamic_scale[index] = 1;
    //=====================================
        /*left forearm*/
        leftforearm_dynamic_translate[index] = 0;
        leftforearm_dynamic_scale[index] = 1;
    //=====================================
        /*right forearm*/
        rightforearm_dynamic_translate[index] = 0;
        rightforearm_dynamic_scale[index] = 1;
    //=====================================
        /*left hand*/
        lefthand_dynamic_translate[index] = 0;
        lefthand_dynamic_scale[index] = 1;
    //=====================================
        /*right hand*/
        righthand_dynamic_translate[index] = 0;
        righthand_dynamic_scale[index] = 1;
    //=====================================
        /*sword*/
        sword_dynamic_translate[index] = 0;
    //=====================================
        /* since we have 3 fingers for each hand,
         * and each finger have one knuckle,
         * we initiate their dynamic variables
         * with a nested for loop
         */
        for(int fingerNumber = 0; fingerNumber < 3; fingerNumber++){
            /*left fingers*/
            leftfingers_dynamic_translate[fingerNumber][index] = 0;
            leftfingers_dynamic_scale[fingerNumber][index] = 1;
            /*right fingers*/
            rightfingers_dynamic_translate[fingerNumber][index] = 0;
            rightfingers_dynamic_scale[fingerNumber][index] = 1;
            /*left finger-knuckles*/
            leftfingerknuckles_dynamic_translate[fingerNumber][index] = 0;
            leftfingerknuckles_dynamic_scale[fingerNumber][index] = 1;
            /*right finger-knuckles*/
            rightfingerknuckles_dynamic_translate[fingerNumber][index] = 0;
            rightfingerknuckles_dynamic_scale[fingerNumber][index] = 1;
        }
    //=====================================
        /* waist don't have translate and scale
         * information to initiate
         */
    //=====================================
        /*left thigh*/
        leftthigh_dynamic_translate[index] = 0;
        leftthigh_dynamic_scale[index] = 1;
    //=====================================
        /*right thigh*/
        rightthigh_dynamic_translate[index] = 0;
        rightthigh_dynamic_scale[index] = 1;
    //=====================================
        /*left shank*/
        leftshank_dynamic_translate[index] = 0;
        leftshank_dynamic_scale[index] = 1;
    //=====================================
        /*right shank*/
        rightshank_dynamic_translate[index] = 0;
        rightshank_dynamic_scale[index] = 1;
    //=====================================
        /*left feet*/
        leftfeet_dynamic_translate[index] = 0;
        leftfeet_dynamic_scale[index] = 1;
    //=====================================
        /*right feet*/
        rightfeet_dynamic_translate[index] = 0;
        rightfeet_dynamic_scale[index] = 0;
    //=====================================
        ground_dynamic_scale[0] = 1;
        ground_dynamic_scale[1] = 1;
        ground_dynamic_scale[2] = 1;
    }
    for(int index = 0; index < 4; index++){
        neck_dynamic_rotate[index] = 0;
        body_dynamic_rotate[index] = 0;
        leftshoulder_dynamic_rotate[index] = 0;
        rightshoulder_dynamic_rotate[index] = 0;
        leftwing_dynamic_rotate[index] = 0;
        rightwing_dynamic_rotate[index] = 0;
        leftarm_dynamic_rotate[index] = 0;
        rightarm_dynamic_rotate[index] = 0;
        leftforearm_dynamic_rotate[index] = 0;
        rightforearm_dynamic_rotate[index] = 0;
        lefthand_dynamic_rotate[index] = 0;
        righthand_dynamic_rotate[index] = 0;
        sword_dynamic_rotate[index] = 0;

        /*finger and finger-knuckles*/
        for(int fingerNumber = 0; fingerNumber < 3; fingerNumber++){
            leftfingers_dynamic_rotate[fingerNumber][index] = 0;
            rightfingers_dynamic_rotate[fingerNumber][index] = 0;
            leftfingerknuckles_dynamic_rotate[fingerNumber][index] = 0;
            rightfingerknuckles_dynamic_rotate[fingerNumber][index] = 0;
        }
        waist_dynamic_rotate[index] = 0;
        leftthigh_dynamic_rotate[index] = 0;
        rightthigh_dynamic_rotate[index] = 0;
        leftshank_dynamic_rotate[index] = 0;
        rightshank_dynamic_rotate[index] = 0;
        leftfeet_dynamic_rotate[index] = 0;
        rightfeet_dynamic_rotate[index] = 0;
    }
}

void CoordinateCalculator::initDefaultCoordinates(){
    standby();
    setStaticCoor();
}

void CoordinateCalculator::setStaticCoor(){
    /*body*/
    BODY_STATIC_POSITION[0] = 0.0f;
    BODY_STATIC_POSITION[1] = 0.0f;
    BODY_STATIC_POSITION[2] = 0.0f;
    BODY_STATIC_ROTATION[0] = 0.0f;
    BODY_STATIC_ROTATION[1] = 0.0f;
    BODY_STATIC_ROTATION[2] = 0.0f;
    BODY_STATIC_ROTATION[3] = 0.0f;
    BODY_STATIC_SCALING[0] = 2.0f;
    BODY_STATIC_SCALING[1] = 3.0f;
    BODY_STATIC_SCALING[2] = 1.5f;
    BODY_STATIC_ORIGINPOS[0] = 0.0f;
    BODY_STATIC_ORIGINPOS[1] = 0.0f;
    BODY_STATIC_ORIGINPOS[2] = 0.0f;
//========================================
    /*head(neck)*/
    NECK_STATIC_POSITION[0] = 0.0f;
    NECK_STATIC_POSITION[1] = 1.0f;
    NECK_STATIC_POSITION[2] = -0.4f;
    NECK_STATIC_ROTATION[0] = 0.0f;
    NECK_STATIC_ROTATION[1] = 0.0f;
    NECK_STATIC_ROTATION[2] = 0.0f;
    NECK_STATIC_ROTATION[3] = 0.0f;
    NECK_STATIC_SCALING[0] = 0.6f;
    NECK_STATIC_SCALING[1] = 1.0f;
    NECK_STATIC_SCALING[2] = 0.6f;
    NECK_STATIC_ORIGINPOS[0] = 0.0f;
    NECK_STATIC_ORIGINPOS[1] = 1.0f;
    NECK_STATIC_ORIGINPOS[2] = 0.0f;
//=======================================
    /*left shoulder*/
    LEFTSHOULDER_STATIC_POSITION[0] = 0.5f;
    LEFTSHOULDER_STATIC_POSITION[1] = 1.3f;
    LEFTSHOULDER_STATIC_POSITION[2] = 0.7f;
    LEFTSHOULDER_STATIC_ROTATION[0] = -20.0f;
    LEFTSHOULDER_STATIC_ROTATION[1] = 0.0f;
    LEFTSHOULDER_STATIC_ROTATION[2] = 1.0f;
    LEFTSHOULDER_STATIC_ROTATION[3] = -0.6f;
    LEFTSHOULDER_STATIC_SCALING[0] = 2.5f;
    LEFTSHOULDER_STATIC_SCALING[1] = 0.3f;
    LEFTSHOULDER_STATIC_SCALING[2] = 0.3f;
    LEFTSHOULDER_STATIC_ORIGINPOS[0] = 1.25f;
    LEFTSHOULDER_STATIC_ORIGINPOS[1] = 0.0f;
    LEFTSHOULDER_STATIC_ORIGINPOS[2] = 0.0f;
//=======================================
    /*right shoulder*/
    RIGHTSHOULDER_STATIC_POSITION[0] = -0.5f;
    RIGHTSHOULDER_STATIC_POSITION[1] = 1.3f;
    RIGHTSHOULDER_STATIC_POSITION[2] = 0.7f;
    RIGHTSHOULDER_STATIC_ROTATION[0] = -20.0f;
    RIGHTSHOULDER_STATIC_ROTATION[1] = 0.0f;
    RIGHTSHOULDER_STATIC_ROTATION[2] = -1.0f;
    RIGHTSHOULDER_STATIC_ROTATION[3] = 0.6f;
    RIGHTSHOULDER_STATIC_SCALING[0] = 2.5f;
    RIGHTSHOULDER_STATIC_SCALING[1] = 0.3f;
    RIGHTSHOULDER_STATIC_SCALING[2] = 0.3f;
    RIGHTSHOULDER_STATIC_ORIGINPOS[0] = -1.25f;
    RIGHTSHOULDER_STATIC_ORIGINPOS[1] = 0.0f;
    RIGHTSHOULDER_STATIC_ORIGINPOS[2] = 0.0f;
//=======================================
    /*left wing*/
    LEFTWING_STATIC_POSITION[0] = 3.1f;
    LEFTWING_STATIC_POSITION[1] = -5.5f;
    LEFTWING_STATIC_POSITION[2] = 0.0f;
    LEFTWING_STATIC_ROTATION[0] = 0.0f;
    LEFTWING_STATIC_ROTATION[1] = 0.0f;
    LEFTWING_STATIC_ROTATION[2] = 0.0f;
    LEFTWING_STATIC_ROTATION[3] = 1.0f;
    LEFTWING_STATIC_SCALING[0] = -1.1f;
    LEFTWING_STATIC_SCALING[1] = 1.1f;
    LEFTWING_STATIC_SCALING[2] = 1.1f;
    LEFTWING_STATIC_ORIGINPOS[0] = 0.0f;
    LEFTWING_STATIC_ORIGINPOS[1] = 0.0f;
    LEFTWING_STATIC_ORIGINPOS[2] = 0.0f;
//=======================================
    /*right wing*/
    RIGHTWING_STATIC_POSITION[0] = -3.1f;
    RIGHTWING_STATIC_POSITION[1] = -5.5f;
    RIGHTWING_STATIC_POSITION[2] = 0.0f;
    RIGHTWING_STATIC_ROTATION[0] = 0.0f;
    RIGHTWING_STATIC_ROTATION[1] = 0.0f;
    RIGHTWING_STATIC_ROTATION[2] = 0.0f;
    RIGHTWING_STATIC_ROTATION[3] = 1.0f;
    RIGHTWING_STATIC_SCALING[0] = 1.1f;
    RIGHTWING_STATIC_SCALING[1] = 1.1f;
    RIGHTWING_STATIC_SCALING[2] = 1.1f;
    RIGHTWING_STATIC_ORIGINPOS[0] = 0.0f;
    RIGHTWING_STATIC_ORIGINPOS[1] = 0.0f;
    RIGHTWING_STATIC_ORIGINPOS[2] = 0.0f;
//=======================================
    /*left arm*/
    LEFTARM_STATIC_POSITION[0] = 1.0f;
    LEFTARM_STATIC_POSITION[1] = 1.0f;
    LEFTARM_STATIC_POSITION[2] = 0.0f;
    LEFTARM_STATIC_ROTATION[0] = 180.0f;
    LEFTARM_STATIC_ROTATION[1] = 1.0f;
    LEFTARM_STATIC_ROTATION[2] = 0.0f;
    LEFTARM_STATIC_ROTATION[3] = 0.0f;
    LEFTARM_STATIC_SCALING[0] = 0.5f;
    LEFTARM_STATIC_SCALING[1] = 1.6f;
    LEFTARM_STATIC_SCALING[2] = 0.8f;
    LEFTARM_STATIC_ORIGINPOS[0] = 0.2f;
    LEFTARM_STATIC_ORIGINPOS[1] = 0.7f;
    LEFTARM_STATIC_ORIGINPOS[2] = 0.0f;
    /*left forearm*/
    LEFTFOREARM_STATIC_POSITION[0] = 0.0f;
    LEFTFOREARM_STATIC_POSITION[1] = 0.8f;
    LEFTFOREARM_STATIC_POSITION[2] = 0.0f;
    LEFTFOREARM_STATIC_ROTATION[0] = 0.0;
    LEFTFOREARM_STATIC_ROTATION[1] = 1.0f;
    LEFTFOREARM_STATIC_ROTATION[2] = 0.0f;
    LEFTFOREARM_STATIC_ROTATION[3] = 0.0f;
    LEFTFOREARM_STATIC_SCALING[0] = 0.5f;
    LEFTFOREARM_STATIC_SCALING[1] = 1.2f;
    LEFTFOREARM_STATIC_SCALING[2] = 0.6f;
    LEFTFOREARM_STATIC_ORIGINPOS[0] = 0.0f;
    LEFTFOREARM_STATIC_ORIGINPOS[1] = 0.7f;
    LEFTFOREARM_STATIC_ORIGINPOS[2] = 0.0f;
    /*left hand*/
    LEFTHAND_STATIC_POSITION[0] = 0.0f;
    LEFTHAND_STATIC_POSITION[1] = 0.6f;
    LEFTHAND_STATIC_POSITION[2] = 0.0f;
    LEFTHAND_STATIC_ROTATION[0] = 0.0;
    LEFTHAND_STATIC_ROTATION[1] = 1.0f;
    LEFTHAND_STATIC_ROTATION[2] = 0.0f;
    LEFTHAND_STATIC_ROTATION[3] = 0.0f;
    LEFTHAND_STATIC_SCALING[0] = 0.2f;
    LEFTHAND_STATIC_SCALING[1] = 0.4f;
    LEFTHAND_STATIC_SCALING[2] = 0.6f;
    LEFTHAND_STATIC_ORIGINPOS[0] = 0.0f;
    LEFTHAND_STATIC_ORIGINPOS[1] = 0.1f;
    LEFTHAND_STATIC_ORIGINPOS[2] = 0.0f;
    /*left fingers*/
    /*left finger 1*/
    LEFTFINGERS_STATIC_POSITION[0][0] = 0.0f;
    LEFTFINGERS_STATIC_POSITION[0][1] = 0.15f;
    LEFTFINGERS_STATIC_POSITION[0][2] = 0.33f;
    LEFTFINGERS_STATIC_ROTATION[0][0] = 15.0f;
    LEFTFINGERS_STATIC_ROTATION[0][1] = 1.0f;
    LEFTFINGERS_STATIC_ROTATION[0][2] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[0][3] = 0.0f;
    LEFTFINGERS_STATIC_SCALING[0][0] = 0.15;
    LEFTFINGERS_STATIC_SCALING[0][1] = 0.4;
    LEFTFINGERS_STATIC_SCALING[0][2] = 0.15;
    LEFTFINGERS_STATIC_ORIGINPOS[0][0] = 0.0f;
    LEFTFINGERS_STATIC_ORIGINPOS[0][1] = 0.2f;
    LEFTFINGERS_STATIC_ORIGINPOS[0][2] = 0.0f;
    /*---------------------------------------*/
    /*left finger 2*/
    LEFTFINGERS_STATIC_POSITION[1][0] = 0.0f;
    LEFTFINGERS_STATIC_POSITION[1][1] = 0.25f;
    LEFTFINGERS_STATIC_POSITION[1][2] = 0.10f;
    LEFTFINGERS_STATIC_ROTATION[1][0] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[1][1] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[1][2] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[1][3] = 0.0f;
    LEFTFINGERS_STATIC_SCALING[1][0] = 0.15;
    LEFTFINGERS_STATIC_SCALING[1][1] = 0.4;
    LEFTFINGERS_STATIC_SCALING[1][2] = 0.15;
    LEFTFINGERS_STATIC_ORIGINPOS[1][0] = 0.0f;
    LEFTFINGERS_STATIC_ORIGINPOS[1][1] = 0.2f;
    LEFTFINGERS_STATIC_ORIGINPOS[1][2] = 0.0f;
    /*---------------------------------------*/
    /*left finger 3*/
    LEFTFINGERS_STATIC_POSITION[2][0] = 0.0f;
    LEFTFINGERS_STATIC_POSITION[2][1] = 0.25f;
    LEFTFINGERS_STATIC_POSITION[2][2] = -0.2f;
    LEFTFINGERS_STATIC_ROTATION[2][0] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[2][1] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[2][2] = 0.0f;
    LEFTFINGERS_STATIC_ROTATION[2][3] = 0.0f;
    LEFTFINGERS_STATIC_SCALING[2][0] = 0.15;
    LEFTFINGERS_STATIC_SCALING[2][1] = 0.4;
    LEFTFINGERS_STATIC_SCALING[2][2] = 0.15;
    LEFTFINGERS_STATIC_ORIGINPOS[2][0] = 0.0f;
    LEFTFINGERS_STATIC_ORIGINPOS[2][1] = 0.2f;
    LEFTFINGERS_STATIC_ORIGINPOS[2][2] = 0.0f;
    /*+++++++++++++++++++++++++++++++++++++++*/
    /*left finger-knuckles*/
    for(int index = 0; index < 3; index ++){
        LEFTFINGERKNUCKLES_STATIC_POSITION[index][0] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_POSITION[index][1] = 0.25f;
        LEFTFINGERKNUCKLES_STATIC_POSITION[index][2] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_ROTATION[index][0] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_ROTATION[index][1] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_ROTATION[index][2] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_ROTATION[index][3] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_SCALING[index][0] = 0.15;
        LEFTFINGERKNUCKLES_STATIC_SCALING[index][1] = 0.2;
        LEFTFINGERKNUCKLES_STATIC_SCALING[index][2] = 0.15;
        LEFTFINGERKNUCKLES_STATIC_ORIGINPOS[index][0] = 0.0f;
        LEFTFINGERKNUCKLES_STATIC_ORIGINPOS[index][1] = 0.1f;
        LEFTFINGERKNUCKLES_STATIC_ORIGINPOS[index][2] = 0.0f;
    }
//=======================================
    /*right arm*/
    RIGHTARM_STATIC_POSITION[0] = -1.0f;
    RIGHTARM_STATIC_POSITION[1] = 1.0f;
    RIGHTARM_STATIC_POSITION[2] = 0.0f;
    RIGHTARM_STATIC_ROTATION[0] = 180.0f;
    RIGHTARM_STATIC_ROTATION[1] = 1.0f;
    RIGHTARM_STATIC_ROTATION[2] = 0.0f;
    RIGHTARM_STATIC_ROTATION[3] = 0.0f;
    RIGHTARM_STATIC_SCALING[0] = 0.5f;
    RIGHTARM_STATIC_SCALING[1] = 1.6f;
    RIGHTARM_STATIC_SCALING[2] = 0.8f;
    RIGHTARM_STATIC_ORIGINPOS[0] = -0.2f;
    RIGHTARM_STATIC_ORIGINPOS[1] = 0.7f;
    RIGHTARM_STATIC_ORIGINPOS[2] = 0.0f;
    /*right forearm*/
    RIGHTFOREARM_STATIC_POSITION[0] = 0.0f;
    RIGHTFOREARM_STATIC_POSITION[1] = 0.8f;
    RIGHTFOREARM_STATIC_POSITION[2] = 0.0f;
    RIGHTFOREARM_STATIC_ROTATION[0] = 0.0;
    RIGHTFOREARM_STATIC_ROTATION[1] = 1.0f;
    RIGHTFOREARM_STATIC_ROTATION[2] = 0.0f;
    RIGHTFOREARM_STATIC_ROTATION[3] = 0.0f;
    RIGHTFOREARM_STATIC_SCALING[0] = 0.5f;
    RIGHTFOREARM_STATIC_SCALING[1] = 1.2f;
    RIGHTFOREARM_STATIC_SCALING[2] = 0.6f;
    RIGHTFOREARM_STATIC_ORIGINPOS[0] = 0.0f;
    RIGHTFOREARM_STATIC_ORIGINPOS[1] = 0.7f;
    RIGHTFOREARM_STATIC_ORIGINPOS[2] = 0.0f;
    /*right hand*/
    RIGHTHAND_STATIC_POSITION[0] = 0.0f;
    RIGHTHAND_STATIC_POSITION[1] = 0.6f;
    RIGHTHAND_STATIC_POSITION[2] = 0.0f;
    RIGHTHAND_STATIC_ROTATION[0] = 0.0;
    RIGHTHAND_STATIC_ROTATION[1] = 1.0f;
    RIGHTHAND_STATIC_ROTATION[2] = 0.0f;
    RIGHTHAND_STATIC_ROTATION[3] = 0.0f;
    RIGHTHAND_STATIC_SCALING[0] = 0.2f;
    RIGHTHAND_STATIC_SCALING[1] = 0.4f;
    RIGHTHAND_STATIC_SCALING[2] = 0.6f;
    RIGHTHAND_STATIC_ORIGINPOS[0] = 0.0f;
    RIGHTHAND_STATIC_ORIGINPOS[1] = 0.1f;
    RIGHTHAND_STATIC_ORIGINPOS[2] = 0.0f;
    /*left fingers*/
    /*left finger 1*/
    RIGHTFINGERS_STATIC_POSITION[0][0] = 0.0f;
    RIGHTFINGERS_STATIC_POSITION[0][1] = 0.15f;
    RIGHTFINGERS_STATIC_POSITION[0][2] = 0.33f;
    RIGHTFINGERS_STATIC_ROTATION[0][0] = 15.0f;
    RIGHTFINGERS_STATIC_ROTATION[0][1] = 1.0f;
    RIGHTFINGERS_STATIC_ROTATION[0][2] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[0][3] = 0.0f;
    RIGHTFINGERS_STATIC_SCALING[0][0] = 0.15;
    RIGHTFINGERS_STATIC_SCALING[0][1] = 0.4;
    RIGHTFINGERS_STATIC_SCALING[0][2] = 0.15;
    RIGHTFINGERS_STATIC_ORIGINPOS[0][0] = 0.0f;
    RIGHTFINGERS_STATIC_ORIGINPOS[0][1] = 0.2f;
    RIGHTFINGERS_STATIC_ORIGINPOS[0][2] = 0.0f;
    /*---------------------------------------*/
    /*left finger 2*/
    RIGHTFINGERS_STATIC_POSITION[1][0] = 0.0f;
    RIGHTFINGERS_STATIC_POSITION[1][1] = 0.25f;
    RIGHTFINGERS_STATIC_POSITION[1][2] = 0.10f;
    RIGHTFINGERS_STATIC_ROTATION[1][0] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[1][1] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[1][2] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[1][3] = 0.0f;
    RIGHTFINGERS_STATIC_SCALING[1][0] = 0.15;
    RIGHTFINGERS_STATIC_SCALING[1][1] = 0.4;
    RIGHTFINGERS_STATIC_SCALING[1][2] = 0.15;
    RIGHTFINGERS_STATIC_ORIGINPOS[1][0] = 0.0f;
    RIGHTFINGERS_STATIC_ORIGINPOS[1][1] = 0.2f;
    RIGHTFINGERS_STATIC_ORIGINPOS[1][2] = 0.0f;
    /*---------------------------------------*/
    /*right finger 3*/
    RIGHTFINGERS_STATIC_POSITION[2][0] = 0.0f;
    RIGHTFINGERS_STATIC_POSITION[2][1] = 0.25f;
    RIGHTFINGERS_STATIC_POSITION[2][2] = -0.2f;
    RIGHTFINGERS_STATIC_ROTATION[2][0] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[2][1] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[2][2] = 0.0f;
    RIGHTFINGERS_STATIC_ROTATION[2][3] = 0.0f;
    RIGHTFINGERS_STATIC_SCALING[2][0] = 0.15;
    RIGHTFINGERS_STATIC_SCALING[2][1] = 0.4;
    RIGHTFINGERS_STATIC_SCALING[2][2] = 0.15;
    RIGHTFINGERS_STATIC_ORIGINPOS[2][0] = 0.0f;
    RIGHTFINGERS_STATIC_ORIGINPOS[2][1] = 0.2f;
    RIGHTFINGERS_STATIC_ORIGINPOS[2][2] = 0.0f;
    /*+++++++++++++++++++++++++++++++++++++++*/
    /*right finger-knuckles*/
    for(int index = 0; index < 3; index ++){
        RIGHTFINGERKNUCKLES_STATIC_POSITION[index][0] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_POSITION[index][1] = 0.25f;
        RIGHTFINGERKNUCKLES_STATIC_POSITION[index][2] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][0] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][1] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][2] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_ROTATION[index][3] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_SCALING[index][0] = 0.15;
        RIGHTFINGERKNUCKLES_STATIC_SCALING[index][1] = 0.2;
        RIGHTFINGERKNUCKLES_STATIC_SCALING[index][2] = 0.15;
        RIGHTFINGERKNUCKLES_STATIC_ORIGINPOS[index][0] = 0.0f;
        RIGHTFINGERKNUCKLES_STATIC_ORIGINPOS[index][1] = 0.1f;
        RIGHTFINGERKNUCKLES_STATIC_ORIGINPOS[index][2] = 0.0f;
    }
//===============================================
    /*waist and legs*/
    WAIST_STATIC_POSITION[0] = 0.0f;
    WAIST_STATIC_POSITION[1] = -1.6f;
    WAIST_STATIC_POSITION[2] = 0.0f;
    WAIST_STATIC_ROTATION[0] = 0.0f;
    WAIST_STATIC_ROTATION[1] = 0.0f;
    WAIST_STATIC_ROTATION[2] = 0.0f;
    WAIST_STATIC_ROTATION[3] = 0.0f;
    WAIST_STATIC_SCALING[0] = 1.2f;
    WAIST_STATIC_SCALING[1] = 0.2f;
    WAIST_STATIC_SCALING[2] = 1.2f;
    WAIST_STATIC_ORIGINPOS[0] = 0.0f;
    WAIST_STATIC_ORIGINPOS[1] = 0.0f;
    WAIST_STATIC_ORIGINPOS[2] = 0.0f;
//===============================================
    /*left leg parts: left-thigh, left-shank, left-feet*/
    /*left-thigh*/
    LEFTTHIGH_STATIC_POSITION[0] = -0.7f;
    LEFTTHIGH_STATIC_POSITION[1] = -0.35f;
    LEFTTHIGH_STATIC_POSITION[2] = 0.0f;
    LEFTTHIGH_STATIC_ROTATION[0] = 0.0f;
    LEFTTHIGH_STATIC_ROTATION[1] = 1.0f;
    LEFTTHIGH_STATIC_ROTATION[2] = 0.0f;
    LEFTTHIGH_STATIC_ROTATION[3] = 0.0f;
    LEFTTHIGH_STATIC_SCALING[0] = 0.6f;
    LEFTTHIGH_STATIC_SCALING[1] = 2.0f;
    LEFTTHIGH_STATIC_SCALING[2] = 0.7f;
    LEFTTHIGH_STATIC_ORIGINPOS[0] = 0.0f;
    LEFTTHIGH_STATIC_ORIGINPOS[1] = -1.0f;
    LEFTTHIGH_STATIC_ORIGINPOS[2] = 0.0f;
    /*left-shank*/
    LEFTSHANK_STATIC_POSITION[0] = 0.0f;
    LEFTSHANK_STATIC_POSITION[1] = -1.22f;
    LEFTSHANK_STATIC_POSITION[2] = 0.0f;
    LEFTSHANK_STATIC_ROTATION[0] = 0.0f;
    LEFTSHANK_STATIC_ROTATION[1] = 1.0f;
    LEFTSHANK_STATIC_ROTATION[2] = 0.0f;
    LEFTSHANK_STATIC_ROTATION[3] = 0.0f;
    LEFTSHANK_STATIC_SCALING[0] = 0.6f;
    LEFTSHANK_STATIC_SCALING[1] = 1.8f;
    LEFTSHANK_STATIC_SCALING[2] = 0.7f;
    LEFTSHANK_STATIC_ORIGINPOS[0] = 0.0f;
    LEFTSHANK_STATIC_ORIGINPOS[1] = -1.0f;
    LEFTSHANK_STATIC_ORIGINPOS[2] = 0.0f;
    /*left feet*/
    LEFTFEET_STATIC_POSITION[0] = 0.0f;
    LEFTFEET_STATIC_POSITION[1] = -1.0f;
    LEFTFEET_STATIC_POSITION[2] = 0.0f;
    LEFTFEET_STATIC_ROTATION[0] = 0.0f;
    LEFTFEET_STATIC_ROTATION[1] = 1.0f;
    LEFTFEET_STATIC_ROTATION[2] = 0.0f;
    LEFTFEET_STATIC_ROTATION[3] = 0.0f;
    LEFTFEET_STATIC_SCALING[0] = 0.8f;
    LEFTFEET_STATIC_SCALING[1] = 0.3f;
    LEFTFEET_STATIC_SCALING[2] = 1.2f;
    LEFTFEET_STATIC_ORIGINPOS[0] = 0.0f;
    LEFTFEET_STATIC_ORIGINPOS[1] = -0.15f;
    LEFTFEET_STATIC_ORIGINPOS[2] = -0.26f;
//======================================
    /*right leg parts: right-thigh, right-shank, right-feet*/
    /*right-thigh*/
    RIGHTTHIGH_STATIC_POSITION[0] = 0.7f;
    RIGHTTHIGH_STATIC_POSITION[1] = -0.35f;
    RIGHTTHIGH_STATIC_POSITION[2] = 0.0f;
    RIGHTTHIGH_STATIC_ROTATION[0] = 0.0f;
    RIGHTTHIGH_STATIC_ROTATION[1] = 1.0f;
    RIGHTTHIGH_STATIC_ROTATION[2] = 0.0f;
    RIGHTTHIGH_STATIC_ROTATION[3] = 0.0f;
    RIGHTTHIGH_STATIC_SCALING[0] = 0.6f;
    RIGHTTHIGH_STATIC_SCALING[1] = 2.0f;
    RIGHTTHIGH_STATIC_SCALING[2] = 0.7f;
    RIGHTTHIGH_STATIC_ORIGINPOS[0] = 0.0f;
    RIGHTTHIGH_STATIC_ORIGINPOS[1] = -1.0f;
    RIGHTTHIGH_STATIC_ORIGINPOS[2] = 0.0f;
    /*right-shank*/
    RIGHTSHANK_STATIC_POSITION[0] = 0.0f;
    RIGHTSHANK_STATIC_POSITION[1] = -1.22f;
    RIGHTSHANK_STATIC_POSITION[2] = 0.0f;
    RIGHTSHANK_STATIC_ROTATION[0] = 0.0f;
    RIGHTSHANK_STATIC_ROTATION[1] = 1.0f;
    RIGHTSHANK_STATIC_ROTATION[2] = 0.0f;
    RIGHTSHANK_STATIC_ROTATION[3] = 0.0f;
    RIGHTSHANK_STATIC_SCALING[0] = 0.6f;
    RIGHTSHANK_STATIC_SCALING[1] = 1.8f;
    RIGHTSHANK_STATIC_SCALING[2] = 0.7f;
    RIGHTSHANK_STATIC_ORIGINPOS[0] = 0.0f;
    RIGHTSHANK_STATIC_ORIGINPOS[1] = -1.0f;
    RIGHTSHANK_STATIC_ORIGINPOS[2] = 0.0f;
    /*right-feet*/
    RIGHTFEET_STATIC_POSITION[0] = 0.0f;
    RIGHTFEET_STATIC_POSITION[1] = -1.0f;
    RIGHTFEET_STATIC_POSITION[2] = 0.0f;
    RIGHTFEET_STATIC_ROTATION[0] = 0.0f;
    RIGHTFEET_STATIC_ROTATION[1] = 1.0f;
    RIGHTFEET_STATIC_ROTATION[2] = 0.0f;
    RIGHTFEET_STATIC_ROTATION[3] = 0.0f;
    RIGHTFEET_STATIC_SCALING[0] = 0.8f;
    RIGHTFEET_STATIC_SCALING[1] = 0.3f;
    RIGHTFEET_STATIC_SCALING[2] = 1.2f;
    RIGHTFEET_STATIC_ORIGINPOS[0] = 0.0f;
    RIGHTFEET_STATIC_ORIGINPOS[1] = -0.15f;
    RIGHTFEET_STATIC_ORIGINPOS[2] = -0.26f;
}

void CoordinateCalculator::moveHand(){
    std::cout << "move hand function called" << std::endl;
    rightarm_dynamic_rotate[1] = 1.0f;
    if(rightarm_dynamic_rotate[0] < 90)
        rightarm_dynamic_rotate[0] += 1.0f;
}

void CoordinateCalculator::summonSword(){
    switch(subState){
    case 0:
        rightarm_dynamic_rotate[1] = 1.0f;
        if(rightarm_dynamic_rotate[0] < 180)
            rightarm_dynamic_rotate[0] += 1.0f;
        righthand_dynamic_rotate[1] = 1.0f;
        if(righthand_dynamic_rotate[0] > -90.0f)
            righthand_dynamic_rotate[0] -= 0.5f;
        if(rightarm_dynamic_rotate[0] >= 180
                && righthand_dynamic_rotate[0] <= -90.0f){
            subState = 1;
            sword_dynamic_translate[2] = 10.0f;
            drawSword = true;
            drawGround = true;
            ground_dynamic_scale[0] = 0.0f;
            ground_dynamic_scale[2] = 0.0f;
        }
        break;
    case 1:
        if(sword_dynamic_translate[2] >= 0.0f)
            sword_dynamic_translate[2] -= 0.1f;
        for(int index = 0; index < 3; index ++){
            rightfingers_dynamic_rotate[index][3] = 1.0f;
            if(rightfingers_dynamic_rotate[index][0] > - 90)
                rightfingers_dynamic_rotate[index][0] --;
        }
        if(ground_dynamic_scale[0] < 10.0f)
            ground_dynamic_scale[0] += 0.03f;
        if(ground_dynamic_scale[2] < 10.0f)
            ground_dynamic_scale[2] += 0.03;
        if(ground_dynamic_scale[0] >= 10.0f
                && ground_dynamic_scale[2] >=10.0f)
            subState = 2;
        break;
    case 2:
        if(ground_dynamic_scale[0] >= 0.0f)
            ground_dynamic_scale[0] -= 0.2f;
        if(ground_dynamic_scale[2] >= 0.0f)
            ground_dynamic_scale[2] -= 0.2f;
        if(ground_dynamic_scale[0] <= 0.1f
                && ground_dynamic_scale[2] <= 0.1f)
            drawGround = false;
        break;
    }
}

void CoordinateCalculator::transformation(){
    drawSword = false;
    switch(subState){
    case 0:
        drawPlaneHead = true;
        ph_dynamic_translate[1] = -2.0f;
        subState = 1;
        break;
    case 1:
        body_dynamic_rotate[2] = 1.0f;
        body_dynamic_rotate[3] = -0.5f;
        if(body_dynamic_rotate[0] < 350)
            body_dynamic_rotate[0] += 1.5;
        if(leftshoulder_dynamic_translate[1] > -2.3f)
            leftshoulder_dynamic_translate[1] -= 0.02f;
        if(rightshoulder_dynamic_translate[1] > -2.3f)
            rightshoulder_dynamic_translate[1] -= 0.02f;
        leftshoulder_dynamic_rotate[3] = 1.0f;
        rightshoulder_dynamic_rotate[3] = 1.0f;
        if(leftshoulder_dynamic_rotate[0] < 80.0f)
            leftshoulder_dynamic_rotate[0]+= 0.9;
        if(rightshoulder_dynamic_rotate[0] > -80.0f)
            rightshoulder_dynamic_rotate[0] -=0.9;
        if(neck_dynamic_translate[1] > -1.5f)
            neck_dynamic_translate[1] -= 0.03;

        if(ph_dynamic_translate[1] < 0.0f)
            ph_dynamic_translate[1] += 0.03;
        if(leftthigh_dynamic_translate[1] < 1.8f)
            leftthigh_dynamic_translate[1] += 0.015;
        if(leftshank_dynamic_translate[1] < 1.8f)
            leftshank_dynamic_translate[1] += 0.015;
        if(rightthigh_dynamic_translate[1] < 1.8f)
            rightthigh_dynamic_translate[1] += 0.015;
        if(rightshank_dynamic_translate[1] < 1.8f)
            rightshank_dynamic_translate[1] += 0.015;
        if(body_dynamic_rotate[0] >= 350)
            subState = 2;
        break;
    case 2:
        mywait ++;
        if(mywait >= 500)
            subState = 3;
        break;
    case 3:
        body_dynamic_rotate[2] = 1.0f;
        body_dynamic_rotate[3] = -0.5f;
        if(body_dynamic_rotate[0] < 720)
            body_dynamic_rotate[0] += 1.5;
        if(leftshoulder_dynamic_translate[1] <= 0.0f)
            leftshoulder_dynamic_translate[1] += 0.02f;
        if(rightshoulder_dynamic_translate[1] <= 0.0f)
            rightshoulder_dynamic_translate[1] += 0.02f;
        leftshoulder_dynamic_rotate[3] = 1.0f;
        rightshoulder_dynamic_rotate[3] = 1.0f;
        if(leftshoulder_dynamic_rotate[0] >= 0.0f)
            leftshoulder_dynamic_rotate[0]-= 0.9;
        if(rightshoulder_dynamic_rotate[0] <= 0.0f)
            rightshoulder_dynamic_rotate[0] +=0.9;
        if(neck_dynamic_translate[1] <= 0.0f)
            neck_dynamic_translate[1] += 0.03;

        if(ph_dynamic_translate[1] > -2.0f)
            ph_dynamic_translate[1] -= 0.03;
        if(leftthigh_dynamic_translate[1] >= 0.0f)
            leftthigh_dynamic_translate[1] -= 0.015;
        if(leftshank_dynamic_translate[1] >= 0.0f)
            leftshank_dynamic_translate[1] -= 0.015;
        if(rightthigh_dynamic_translate[1] >= 0.0f)
            rightthigh_dynamic_translate[1] -= 0.015;
        if(rightshank_dynamic_translate[1] >= 0.0f)
            rightshank_dynamic_translate[1] -= 0.015;
        if(body_dynamic_rotate[0] >= 720){
            drawPlaneHead = false;
            mywait = 0;
        }
        break;
    }
}
//=======================================
void CoordinateCalculator::rightShowStone()
{
   rightfingers_dynamic_rotate[0][3] = 1.0f;
   if(rightfingers_dynamic_rotate[0][0] > -60)
       rightfingers_dynamic_rotate[0][0] -= 2.0f;
   rightfingers_dynamic_rotate[1][3] = 1.0f;
   if(rightfingers_dynamic_rotate[1][0] > -60)
       rightfingers_dynamic_rotate[1][0] -= 2.0f;
   rightfingers_dynamic_rotate[2][3] = 1.0f;
   if(rightfingers_dynamic_rotate[2][0] > -60)
       rightfingers_dynamic_rotate[2][0] -= 2.0f;

   rightfingerknuckles_dynamic_rotate[0][3] = 1.0f;
   if(rightfingerknuckles_dynamic_rotate[0][0] > -90)
       rightfingerknuckles_dynamic_rotate[0][0] -= 2.0f;
   rightfingerknuckles_dynamic_rotate[1][3] = 1.0f;
   if(rightfingerknuckles_dynamic_rotate[1][0] > -90)
       rightfingerknuckles_dynamic_rotate[1][0] -= 2.0f;
   rightfingerknuckles_dynamic_rotate[2][3] = 1.0f;
   if(rightfingerknuckles_dynamic_rotate[2][0] > -90)
       rightfingerknuckles_dynamic_rotate[2][0] -= 2.0f;
}

void CoordinateCalculator::leftShowStone()
{
   leftfingers_dynamic_rotate[0][3] = 1.0f;
   if(leftfingers_dynamic_rotate[0][0] < 60)
       leftfingers_dynamic_rotate[0][0] += 2.0f;
   leftfingers_dynamic_rotate[1][3] = 1.0f;
   if(leftfingers_dynamic_rotate[1][0] < 60)
       leftfingers_dynamic_rotate[1][0] += 2.0f;
   leftfingers_dynamic_rotate[2][3] = 1.0f;
   if(leftfingers_dynamic_rotate[2][0] < 60)
       leftfingers_dynamic_rotate[2][0] += 2.0f;

   leftfingerknuckles_dynamic_rotate[0][3] = 1.0f;
   if(leftfingerknuckles_dynamic_rotate[0][0] <  90)
       leftfingerknuckles_dynamic_rotate[0][0] += 2.0f;
   leftfingerknuckles_dynamic_rotate[1][3] = 1.0f;
   if(leftfingerknuckles_dynamic_rotate[1][0] <  90)
       leftfingerknuckles_dynamic_rotate[1][0] += 2.0f;
   leftfingerknuckles_dynamic_rotate[2][3] = 1.0f;
   if(leftfingerknuckles_dynamic_rotate[2][0] <  90)
       leftfingerknuckles_dynamic_rotate[2][0] += 2.0f;
}

void CoordinateCalculator::yesPose()
{
    std::cout << "yes pose function called" << std::endl;
    if(subState == 1 && leftarm_dynamic_rotate[0] != -30)
        subState = 0;

    leftarm_dynamic_rotate[3] = 1.0f;
    if(leftarm_dynamic_rotate[0] > -30)
        leftarm_dynamic_rotate[0] -= 1.0f;
    leftforearm_dynamic_rotate[3] = 1.0f;
    if(leftforearm_dynamic_rotate[0] < 60)
        leftforearm_dynamic_rotate[0] += 2.0f;

    if(rightarm_dynamic_rotate[0] > -90 && subState == 0)
    {
       rightarm_dynamic_rotate[1] = 1.0f;
       if(rightarm_dynamic_rotate[0] <  90)
           rightarm_dynamic_rotate[0] += 2.0f;
       rightforearm_dynamic_rotate[1] = 1.0f;
       if(rightforearm_dynamic_rotate[0] <  90)
           rightforearm_dynamic_rotate[0] += 2.0f;
     }

    if(righthand_dynamic_rotate[0] <  90 && subState == 0)
    {
       righthand_dynamic_rotate[2] = 1.0f;
       if(righthand_dynamic_rotate[0] > -90)
           righthand_dynamic_rotate[0] -= 2.0f;
    }

    rightShowStone();

    if(rightarm_dynamic_rotate[0] ==  90)
        subState = 1;

    if(subState == 1)
    {
        rightarm_dynamic_rotate[1] = 1.0f;
        if(rightarm_dynamic_rotate[0] > -20)
            rightarm_dynamic_rotate[0] -= 2.0f;
        rightforearm_dynamic_rotate[1] = 1.0f;
        if(rightforearm_dynamic_rotate[0] < 120)
            rightforearm_dynamic_rotate[0] += 1.0f;
    }
}

void CoordinateCalculator::runing()
{
    std::cout << "runing function called" << std::endl;
    rightShowStone();
    leftShowStone();

//    if(rightarm_dynamic_rotate[0] < 60)
//    {
//        rightarm_dynamic_rotate[2] = 1.0f;
//        if(rightarm_dynamic_rotate[0] < 60)
//            rightarm_dynamic_rotate[0] += 2.5f;
//    }

    if(rightarm_dynamic_rotate[0] < 90 && leftarm_dynamic_rotate[0] > -90 && subState == 0)
    {
        rightarm_dynamic_rotate[1] = 1.0f;
        if(rightarm_dynamic_rotate[0] < 90)
            rightarm_dynamic_rotate[0] += 3.0f;
        rightforearm_dynamic_rotate[1] = 1.0f;
        if(rightforearm_dynamic_rotate[0] <  90)
           rightforearm_dynamic_rotate[0] += 3.0f;
        leftarm_dynamic_rotate[1] = 1.0f;
        if(leftarm_dynamic_rotate[0] > -90)
            leftarm_dynamic_rotate[0] -= 3.0f;
        leftforearm_dynamic_rotate[1] = 1.0f;
        if(leftforearm_dynamic_rotate[0] <  90)
          leftforearm_dynamic_rotate[0] += 3.0f;


        rightthigh_dynamic_rotate[1] = 1.0f;
        if(rightthigh_dynamic_rotate[0] <  60)
            rightthigh_dynamic_rotate[0] += 1.8f;
        rightshank_dynamic_rotate[1] = 1.0f;
        if(rightshank_dynamic_rotate[0] > -60)
            rightshank_dynamic_rotate[0] -= 1.8f;
        leftthigh_dynamic_rotate[1] = 1.0f;
        if(leftthigh_dynamic_rotate[0] > -60)
            leftthigh_dynamic_rotate[0] -= 1.8f;
        leftshank_dynamic_rotate[1] = 1.0f;
        if(leftshank_dynamic_rotate[0] > -60)
            leftshank_dynamic_rotate[0] -= 1.8f;
    }

    if(rightarm_dynamic_rotate[0] > -90 && leftarm_dynamic_rotate[0] < 90 && subState == 1)
    {
        rightarm_dynamic_rotate[1] = 1.0f;
        if(rightarm_dynamic_rotate[0] > -90)
            rightarm_dynamic_rotate[0] -= 3.0f;
        rightforearm_dynamic_rotate[1] = 1.0f;
        if(rightforearm_dynamic_rotate[0] <  90)
            rightforearm_dynamic_rotate[0] += 3.0f;
        leftarm_dynamic_rotate[1] = 1.0f;
        if(leftarm_dynamic_rotate[0] < 90)
            leftarm_dynamic_rotate[0] += 3.0f;
        leftforearm_dynamic_rotate[1] = 1.0f;
        if(leftforearm_dynamic_rotate[0] <  90)
            leftforearm_dynamic_rotate[0] += 3.0f;


        rightthigh_dynamic_rotate[1] = 1.0f;
        if(rightthigh_dynamic_rotate[0] > -60)
            rightthigh_dynamic_rotate[0] -= 1.8f;
        rightshank_dynamic_rotate[1] = 1.0f;
        if(rightshank_dynamic_rotate[0] > -60)
            rightshank_dynamic_rotate[0] -= 1.8f;
        leftthigh_dynamic_rotate[1] = 1.0f;
        if(leftthigh_dynamic_rotate[0] <  60)
            leftthigh_dynamic_rotate[0] += 1.8f;
        leftshank_dynamic_rotate[1] = 1.0f;
        if(leftshank_dynamic_rotate[0] > -60)
            leftshank_dynamic_rotate[0] -= 1.8f;
    }

    if(     rightarm_dynamic_rotate[0] == -90 && leftarm_dynamic_rotate[0] ==  90 && subState == 1)
        subState = 0;
    else if(rightarm_dynamic_rotate[0] ==  90 && leftarm_dynamic_rotate[0] == -90 && subState == 0)
        subState = 1;
}

void CoordinateCalculator::walk()
{
    std::cout << "walk function called" << std::endl;
    if(rightarm_dynamic_rotate[0] < 60 && leftarm_dynamic_rotate[0] > -60 && subState == 0)
    {
        rightarm_dynamic_rotate[1] = 1.0f;
        if(rightarm_dynamic_rotate[0] < 20)
            rightarm_dynamic_rotate[0] += 0.5f;
        rightforearm_dynamic_rotate[1] = 1.0f;
        if(rightforearm_dynamic_rotate[0] <  20)
           rightforearm_dynamic_rotate[0] += 0.5f;
        leftarm_dynamic_rotate[1] = 1.0f;
        if(leftarm_dynamic_rotate[0] > -20)
            leftarm_dynamic_rotate[0] -= 0.5f;
        leftforearm_dynamic_rotate[1] = 1.0f;
        if(leftforearm_dynamic_rotate[0] <  20)
          leftforearm_dynamic_rotate[0] += 0.5f;


        rightthigh_dynamic_rotate[1] = 1.0f;
        if(rightthigh_dynamic_rotate[0] <  30)
            rightthigh_dynamic_rotate[0] += 0.8f;
        rightshank_dynamic_rotate[1] = 1.0f;
        if(rightshank_dynamic_rotate[0] > -30)
            rightshank_dynamic_rotate[0] -= 0.8f;
        leftthigh_dynamic_rotate[1] = 1.0f;
        if(leftthigh_dynamic_rotate[0] > -30)
            leftthigh_dynamic_rotate[0] -= 0.8f;
        leftshank_dynamic_rotate[1] = 1.0f;
        if(leftshank_dynamic_rotate[0] < 0)
            leftshank_dynamic_rotate[0] += 0.8f;
    }

    if(subState == 1)
    {
        rightarm_dynamic_rotate[1] = 1.0f;
        if(rightarm_dynamic_rotate[0] > -20)
            rightarm_dynamic_rotate[0] -= 0.5f;
        rightforearm_dynamic_rotate[1] = 1.0f;
        if(rightforearm_dynamic_rotate[0] <  20)
            rightforearm_dynamic_rotate[0] += 0.5f;
        leftarm_dynamic_rotate[1] = 1.0f;
        if(leftarm_dynamic_rotate[0] < 20)
            leftarm_dynamic_rotate[0] += 0.5f;
        leftforearm_dynamic_rotate[1] = 1.0f;
        if(leftforearm_dynamic_rotate[0] <  20)
            leftforearm_dynamic_rotate[0] += 0.5f;

        rightshank_dynamic_rotate[1] = 1.0f;
        if(rightshank_dynamic_rotate[0] < 0)
            rightshank_dynamic_rotate[0] += 0.8f;
        rightthigh_dynamic_rotate[1] = 1.0f;
        if(rightthigh_dynamic_rotate[0] > -30)
            rightthigh_dynamic_rotate[0] -= 0.8f;
        leftthigh_dynamic_rotate[1] = 1.0f;
        if(leftthigh_dynamic_rotate[0] <  30)
            leftthigh_dynamic_rotate[0] += 0.8f;
        leftshank_dynamic_rotate[1] = 1.0f;
        if(leftshank_dynamic_rotate[0] > -30)
            leftshank_dynamic_rotate[0] -= 0.8f;
    }

    if(     rightarm_dynamic_rotate[0] ==  20 && leftarm_dynamic_rotate[0] == -20 && subState == 0)
        subState = 1;
    else if(rightarm_dynamic_rotate[0] == -20 && leftarm_dynamic_rotate[0] ==  20 && subState == 1)
        subState = 0;
}

void CoordinateCalculator::angry()
{
    std::cout << "angry function called" << std::endl;
    rightarm_dynamic_rotate[2] = 1.0f;
    if(rightarm_dynamic_rotate[0] < 0)
        rightarm_dynamic_rotate[0] += 0.8f;
}

void CoordinateCalculator::test()
{
    std::cout << "TEST~" << std::endl;
}
