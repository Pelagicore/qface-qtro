from setuptools import setup, find_packages

setup(
    name='qface-qtro',
    version='1.3',
    description='Generator based on the QFace library for QtRemoteObjects',
    url='https://github.com/Pelagicore/qface-qtro',
    author='jryannel',
    author_email='juergen@ryannel.org',
    license='MIT',
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Code Generators',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
    ],
    keywords='qt ipc generator',
    packages=find_packages(),
    include_package_data=True,
    package_data={
        '': ['*']
    },
    install_requires=[
        'qface>=1.3.1',
    ],
    entry_points={
        'console_scripts': [
            'qface-qtro = qtro.qtro:app'
        ],
    },
)
