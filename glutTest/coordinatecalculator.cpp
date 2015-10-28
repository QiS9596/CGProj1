#include "coordinatecalculator.h"

CoordinateCalculator::CoordinateCalculator()
{

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
        righthand_dynamic rotate[index] = 0;
        /*finger and finger-knuckles*/
        for(int fingerNumber = 0; fingerNumber < 3; fingerNumber++){
            leftfingers_dynamic_rotate[fingerNumber][index] = 0;
            rightfingers_dynamic_rotate[fingerNumber][index] = 0;
            leftfingerknuckles_dynamic_rotate[fingerNumber][index] = 0;
            rightfingerknuckles_dynamic rotate[fingerNumber][index] = 0;
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

}
