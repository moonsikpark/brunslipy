from distutils.core import setup, Extension


def main():
    setup(
        name="brunslipy",
        version="1.0.0",
        description="Python binding for brunsli",
        author="Moonsik Park",
        author_email="mooonsik.park@gmail.com",
        ext_modules=[
            Extension(
                "brunsli",
                sources=["common.c", "brunsli_binding.c"],
                libraries = ['brunslienc-c', 'brunslidec-c'],
            )
        ],
    )


if __name__ == "__main__":
    main()
