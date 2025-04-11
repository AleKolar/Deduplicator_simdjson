from setuptools import setup, Extension

module = Extension(
    'simdjson_parser',
    sources=['simdjson_module.cpp'],
    libraries=['simdjson'],
    extra_compile_args=['-O3', '-march=native']
)

setup(
    name='simdjson_parser',
    version='1.0',
    ext_modules=[module]
)

# компилируем модуль python setup.py build_ext --inplace