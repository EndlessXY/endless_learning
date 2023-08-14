import cv2
import numpy as np
import rclpy
from cv_bridge import CvBridge
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import CompressedImage
from sensor_msgs.msg import Image

class Logic(Node):
    def __init__(self, name):
        super().__init__(name)
        qos_prof_file = QoSProfile(depth=2)
        qos_prof_file.reliability = ReliabilityPolicy.RMW_QOS_POLICY_RELIABILITY_RELIABLE

        self.sonar_image_sub = self.create_subscription(Image, "sonar/image_raw", self.sonar_image_listener_callback, qos_prof_file)
        self.bridge = CvBridge()
        self.cache_image = np.zeros((960, 1920, 3), dtype=np.uint8)
        self.current_row = 0

    def update_cache(self, new_row_mat):
        new_row = np.array(new_row_mat)

        assert new_row.shape == (1, self.cache_image.shape[1], self.cache_image.shape[2]), "New row shape doesn't match cache width and channels"
        self.cache_image[1:] = self.cache_image[:-1]
        self.cache_image[0] = new_row

    def sonar_image_listener_callback(self, ros_data):
        self.current_row += 1
        cv_image = self.bridge.imgmsg_to_cv2(ros_data, "bgr8")
        # self.update_cache(cv_image)
        self.get_logger().info(f"Received Image: {self.current_row}")
        # cv2.imshow('Received Image', self.cache_image)
        cv2.imshow('Received Image', cv_image)
        cv2.waitKey(5)



def main(args=None):
    rclpy.init(args=args)
    node = Logic("logic")
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()