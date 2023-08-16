from setuptools import find_packages, setup

package_name = 'test_service_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='dsz',
    maintainer_email='dengshizhe96@outlook.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'service_adder_client  = test_service_py.service_adder_client:main',
            'service_adder_server  = test_service_py.service_adder_server:main',
        ],
    },
)
