# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM rikorose/gcc-cmake:latest as build

# Установим рабочую директорию для сборки GoogleTest
WORKDIR /gtest_build

# Скачаем все необходимые пакеты и выполним сборку GoogleTest
# Такая длинная команда обусловлена тем, что
# Docker на каждый RUN порождает отдельный слой,
# Влекущий за собой, в данном случае, ненужный оверхед
RUN DEBIAN_FRONTEND="noninteractive" apt-get update && \
    apt-get install -y \
      libboost-dev libboost-program-options-dev \
      libgtest-dev \
    && \
    cmake -DCMAKE_BUILD_TYPE=Release /usr/src/gtest && \
    cmake --build . && \
    mv lib*.a /usr/lib

# Скопируем директорию /src в контейнер
ADD src /app/src

# Установим рабочую директорию для сборки проекта
WORKDIR /app/build

# Выполним сборку нашего проекта, а также его тестирование
#cmake --build . --config $BUILD_TYPE --target Tests
RUN cmake ../src && \
    cmake --build . && \
    CTEST_OUTPUT_ON_FAILURE=TRUE cmake --build . --target Tests

# Запуск ---------------------------------------

# В качестве базового образа используем ubuntu:latest
FROM rikorose/gcc-cmake:latest

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata valgrind ssh


# Добавим пользователя, потому как в Docker по умолчанию используется root
# Запускать незнакомое приложение под root'ом неприлично :)
#RUN groupadd -r docker && useradd -r -g docker docker
#USER docker
RUN useradd -m user \
  && yes password | passwd user

RUN usermod -s /bin/bash user

# Установим рабочую директорию нашего приложения
WORKDIR /app

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test \
  && mkdir /run/sshd

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY --from=build /app/build/Laba2 .
COPY --from=build /app/build/Tests/Tests .

# Установим точку входа
#ENTRYPOINT ["./hello_world_app"]
CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test"]