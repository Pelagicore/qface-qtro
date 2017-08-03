from setuptools import setup, find_packages
from path import Path
from qtro import __about__ as about

here = Path(__file__).abspath().dirname()
readme = Path(here / 'README.md').text()

setup(
    name=about.__title__,
    version=about.__version__,
    description=about.__description__,
    long_description=readme,
    url=about.__url__,
    author=about.__author__,
    author_email=about.__author_email__,
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
    install_requires=[
        'qface>=1.8',
        'click',
        'PyYAML',
        'Jinja2',
        'path.py'
    ],
    entry_points={
        'console_scripts': [
            'qface-qtro = qtro.qtro:app'
        ],
    },
)
