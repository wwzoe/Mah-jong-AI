#!/usr/bin/env python

from distutils.core import setup, Extension

example_module = Extension('_client',
                           sources=['client.c',
                                    'client_wrap.c',
                                    'sysdep.c',
                                    'game.c',
                                    'protocol.c',
                                    'tiles.c',
                                    'player.c',
                                    'protocol_helper.c',
                                    'client_helper.c'])

setup(name='client',
      version='0.1',
      author='SWIG',
      description="""Client""",
      ext_modules=[example_module],
      py_modules=['client'])
