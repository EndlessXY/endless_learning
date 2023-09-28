import rclpy
from rclpy.node import Node
from test_interfaces.srv import NumberToWords


class NumberToWordsClient(Node):
    def __init__(self):
        super().__init__('number_to_words_client')
        self.cli = self.create_client(NumberToWords, 'number_to_words')
        self.call_service()

    def call_service(self):
        request = NumberToWords.Request()
        request.number = int(input("Enter a number (1-9): "))

        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')

        self.future = self.cli.call_async(request)

        rclpy.spin_until_future_complete(self, self.future)

        if self.future.result() is not None:
            response = self.future.result()
            result_dict = {i + 1: word for i, word in enumerate(response.words)}
            print(result_dict)
        else:
            self.get_logger().info('Service call failed.')


def main(args=None):
    rclpy.init(args=args)
    client = NumberToWordsClient()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
