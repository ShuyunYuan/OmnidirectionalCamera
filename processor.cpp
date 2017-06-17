/*------------------------------------------------------------------------------
   Example code that shows the use of the 'cam2world" and 'world2cam" functions
   Shows also how to undistort images into perspective or panoramic images

   NOTE, IF YOU WANT TO SPEED UP THE REMAP FUNCTION I STRONGLY RECOMMEND TO INSTALL
   INTELL IPP LIBRARIES ( http://software.intel.com/en-us/intel-ipp/ )
   YOU JUST NEED TO INSTALL IT AND INCLUDE ipp.h IN YOUR PROGRAM

   Copyright (C) 2009 DAVIDE SCARAMUZZA, ETH Zurich
   Author: Davide Scaramuzza - email: davide.scaramuzza@ieee.org
------------------------------------------------------------------------------*/

#include <cstdio>

#include "ocam_functions.h"

using namespace cv;

IplImage *processFile(const char* fileName) {

    /* --------------------------------------------------------------------*/
    /* Read the parameters of the omnidirectional camera from the TXT file */
    /* --------------------------------------------------------------------*/
    struct ocam_model o, o_cata; // our ocam_models for the fisheye and catadioptric cameras
    get_ocam_model(&o, "./calib_results_fisheye.txt");
    get_ocam_model(&o_cata, "./calib_results_catadioptric.txt");
    /* --------------------------------------------------------------------*/
    /* Print ocam_model parameters                                         */
    /* --------------------------------------------------------------------*/
    int i;
    printf("pol =\n");
    for (i = 0; i < o.length_pol; i++) {
        printf("\t%e\n", o.pol[i]);
    };
    printf("\n");
    printf("invpol =\n");
    for (i = 0; i < o.length_invpol; i++) {
        printf("\t%e\n", o.invpol[i]);
    };
    printf("\n");
    printf("\nxc = %f\nyc = %f\n\nwidth = %d\nheight = %d\n", o.xc, o.yc, o.width, o.height);

    /* --------------------------------------------------------------------*/
    /* Allocate space for the unistorted images                            */
    /* --------------------------------------------------------------------*/
    IplImage *src2 = cvLoadImage(fileName);
    CvSize size_pan_image = cvSize(1200, 400);        // size of the undistorted panoramic image
    IplImage *dst_pan = cvCreateImage(size_pan_image, 8, 3);    // undistorted panoramic image

    CvMat *mapx_pan = cvCreateMat(dst_pan->height, dst_pan->width, CV_32FC1);
    CvMat *mapy_pan = cvCreateMat(dst_pan->height, dst_pan->width, CV_32FC1);

    /* --------------------------------------------------------------------  */
    /* Create Look-Up-Table for panoramic undistortion                       */
    /* The undistortoin is just a simple cartesia-to-polar transformation    */
    /* Note, only the knowledge of image center (xc,yc) is used to undisort the image      */
    /* xc, yc are the row and column coordinates of the image center         */
    /* Note, if you would like to flip the image, just inverte the sign of theta in this function */
    /* --------------------------------------------------------------------  */
    //float Rmax = 470;  // the maximum radius of the region you would like to undistort into a panorama
    //float Rmin = 20;   // the minimum radius of the region you would like to undistort into a panorama
    //Edited by Huang
    o_cata.xc = 537;
    o_cata.yc = 799; // 直接写了圆心坐标
    float Rmax = 420;  // the maximum radius of the region you would like to undistort into a panorama
    float Rmin = 110;   // the minimum radius of the region you would like to undistort into a panorama
    //edit End
    create_panoramic_undistortion_LUT(mapx_pan, mapy_pan, Rmin, Rmax, o_cata.xc, o_cata.yc);

    /* --------------------------------------------------------------------*/
    /* Undistort using specified interpolation method                      */
    /* Other possible values are (see OpenCV doc):                         */
    /* CV_INTER_NN - nearest-neighbor interpolation,                       */
    /* CV_INTER_LINEAR - bilinear interpolation (used by default)          */
    /* CV_INTER_AREA - resampling using pixel area relation. It is the preferred method for image decimation that gives moire-free results. In case of zooming it is similar to CV_INTER_NN method. */
    /* CV_INTER_CUBIC - bicubic interpolation.                             */
    /* --------------------------------------------------------------------*/
    cvRemap(src2, dst_pan, mapx_pan, mapy_pan, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));

    /* --------------------------------------------------------------------*/
    /* Save image                                                          */
    /* --------------------------------------------------------------------*/
    cvSaveImage("undistorted_panoramic.jpg", dst_pan);

    /* --------------------------------------------------------------------*/
    /* Free memory                                                         */
    /* --------------------------------------------------------------------*/
    cvReleaseImage(&src2);
    //cvReleaseImage(&dst_pan);
    cvReleaseMat(&mapx_pan);
    cvReleaseMat(&mapy_pan);

    return dst_pan;
}
