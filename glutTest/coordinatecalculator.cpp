#include "coordinatecalculator.h"

CoordinateCalculator::CoordinateCalculator()
{
    initDefaultCoordinates();
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
    //==================
        /*neck*/
        neck_dynamic_translate[index] = 0;
        neck_dynamic_scale[index] = 1;
    //=====================================
        /*body*/
        body_dynamic_translate[index] = 0;
        body_dynamic_scale[index] = 1;
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
    }
    for(int index = 0; index < 4; index++){
        neck_dynamic_rotate[index] = 0;
        body_dynamic_rotate[index] = 0;
        leftarm_dynamic_rotate[index] = 0;
        rightarm_dynamic_rotate[index] = 0;
        leftforearm_dynamic_rotate[index] = 0;
        rightforearm_dynamic_rotate[index] = 0;
        lefthand_dynamic_rotate[index] = 0;
        righthand_dynamic_rotate[index] = 0;
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
    NECK_STATIC_POSITION[2] = 0.0f;
    NECK_STATIC_ROTATION[0] = 0.0f;
    NECK_STATIC_ROTATION[1] = 0.0f;
    NECK_STATIC_ROTATION[2] = 0.0f;
    NECK_STATIC_ROTATION[3] = 0.0f;
    NECK_STATIC_SCALING[0] = 1.0f;
    NECK_STATIC_SCALING[1] = 1.0f;
    NECK_STATIC_SCALING[2] = 1.0f;
    NECK_STATIC_ORIGINPOS[0] = 0.0f;
    NECK_STATIC_ORIGINPOS[1] = 1.0f;
    NECK_STATIC_ORIGINPOS[2] = 0.0f;
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
}
