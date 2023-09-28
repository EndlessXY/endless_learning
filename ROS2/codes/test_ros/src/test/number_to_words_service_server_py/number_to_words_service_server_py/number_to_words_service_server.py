import rclpy
from rclpy.node import Node
from test_interfaces.srv import NumberToWords


class NumberToWordsService(Node):
    def __init__(self):
        super().__init__('number_to_words_service')
        self.srv = self.create_service(NumberToWords, 'number_to_words', self.callback)

    def callback(self, request, response):
        num_to_word = {
            1: "one",
            2: "two",
            3: "three",
            4: "four",
            5: "five",
            6: "six",
            7: "seven",
            8: "eight",
            9: "nine"
        }

        for i in range(1, request.number + 1):
            if i in num_to_word:
                response.words.append(num_to_word[i])
        return response


def main(args=None):
    rclpy.init(args=args)
    service = NumberToWordsService()
    rclpy.spin(service)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
