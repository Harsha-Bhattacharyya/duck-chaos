# Maintainer: Harsha Bhattacharyya <harshabhattacharyya510@duck.com>
pkgname=duck-chaos
pkgdesc='Fun Duck annoyance sim'
pkgver=1.0
pkgrel=1
arch=('x86_64')
url="https://github.com/Harsha-Bhattacharyya/duck-chaos.git"
license=('MIT')
depends=('bash')
makedepends=('gcc')
source=("duck-chaos.c"
        "duck.mp4"
        "lavendertown.mp3"
        "duck.jpeg")
sha256sums=('e99c68122991171402c5fc60af21124b85aa189b002a0d36b7e02af2dceee7d6  duck-chaos.c'
            '3da23f13745041828267cf3d18e0849f1fb0c42fcc50deabb839c3971d3f89fe  duck.mp4'
            'abdbc94cb77431d498abc004197a018480c89edf0ecaa3fe247ddc9efc01e029  lavendertown.mp3'
            '917041365397517900feb5132129addee613e023163e4b9dd98f584bbcff76d6  duck.jpeg')
install=$pkgname.install

build() {
    gcc duck-chaos.c -o duck-chaos
}

package() {
    # Install binary
    install -Dm755 duck-chaos "$pkgdir/usr/bin/duck-chaos"

    # Install video, audio, and image assets
    install -Dm644 duck.mp4 "$pkgdir/usr/share/duck-chaos/duck.mp4"
    install -Dm644 lavendertown.mp3 "$pkgdir/usr/share/duck-chaos/lavendertown.mp3"
    install -Dm644 duck.jpeg "$pkgdir/usr/share/duck-chaos/duck.jpeg"
}

