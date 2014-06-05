EfficientLargeScaleStereo
=========================
A wrapper of the stereo matcher (LIBELAS: Library for Efficient Large-scale Stereo Matching) for OpenCV.
http://www.cvlibs.net/software/libelas/

Usage
=====
* The output disparity map is x16 scaled, and stored in CV_16S (short type).  
* The last parameter of "int border" controls the size of image border for left or right size of occlusions.  


        Mat leftim;
        Mat rightim;
        Mat dest;
        
        //set min disparity and max disparity
        StereoEfficientLargeScale elas(0,128);
        
        // we can set additional parameters;
                //elas.elas.param.ipol_gap_width=;
                //elas.elas.param.speckle_size=getParameter("speckle_size");
                //elas.elas.param.speckle_sim_threshold=getParameter("speckle_sim");
        
        //do stereo matching.
        elas(leftim,rightim,dest,100);

Information of Paper
====================
        @INPROCEEDINGS{Geiger2010ACCV,
          author = {Andreas Geiger and Martin Roser and Raquel Urtasun},
          title = {Efficient Large-Scale Stereo Matching},
          booktitle = {Asian Conference on Computer Vision (ACCV)},
          year = {2010}
        }



License
=======
The based code is GPL, thus this code is also published under the GNU General Public License.
