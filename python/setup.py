#######################################################################
# Company      :  zmokewares
# Author       : Hans Erik Fjeld
#######################################################################
# All Rights Reserved


# import os
from setuptools import setup, find_packages

setup(
    name='filtcalc',
    version='0.5.0',
    description='IIR Filter tool',
    long_description="Scilab IIR Coefficient generator.",
    author='hans.erik.fjeld',
    author_email='hanse.fjeld@gmail.com',
    url='',
    packages=find_packages(),
    setup_requires=['wheel'],
    install_requires=['scipy', 'numpy', 'matplotlib', 'pandas'],
    include_package_data=True,
    package_data={
        'filtcalc.static': ['*.json'],
    },
    entry_points={
        'console_scripts': [
            'filtcalc=iir_filter.py.main:main'
        ],
    }
)


'''
    


'''
