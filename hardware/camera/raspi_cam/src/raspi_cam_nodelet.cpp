#include <raspi_cam/raspi_cam_nodelet.h>
#include <pluginlib/class_list_macros.h>


PLUGINLIB_EXPORT_CLASS(raspi_cam::RaspiCamNodelet, nodelet::Nodelet)

namespace raspi_cam
{
    void RaspiCamNodelet::onInit()
    {
        Setup(getNodeHandle());
        runPublisher();
    }

    void RaspiCamNodelet::Setup(ros::NodeHandle nh)
    {
        nh_ = nh;
        it_ = image_transport::ImageTransport(nh_);
        image_pub_ = it_.advertise("/camera/image", 1);
    }

    void RaspiCamNodelet::runPublisher()
    {
        cv::Mat image_upsdwn;
        cv::Mat image;
        cv_bridge::CvImagePtr cv_ptr;
        sensor_msgs::ImagePtr msg;
        while(ros::ok())
        {
            try
            {
                camera_.retrieve(image_upsdwn);
                cv::rotate(image_upsdwn, image, cv::ROTATE_180);
                msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
                image_pub_.publish(msg);
            }
            catch(...)
            {
                ROS_ERROR("Error in raspi camera image publisher.\n");
                return;
            }
        }
    }
}