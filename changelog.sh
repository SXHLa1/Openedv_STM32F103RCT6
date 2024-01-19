#!/usr/bin/env bash
#
# Copyright 2020-2023 eliu (eliuhy@163.com)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
set -o errexit

readonly PROG=$(basename $0)
readonly VERSION="v1.0.5"
readonly GRN="\e[32m" # green color
readonly YLW="\e[33m" # yellow color
readonly RED="\e[91m" # red color
readonly RST="\e[39m" # reset color
readonly FMT_TEXT="text"
readonly FMT_MARKDOWN="markdown"

VERSION_FROM=   # 拉取日志的提交ID下限
VERSION_TO=     # 拉取日志的提交ID上限
COMMIT_RANGE=   # 拉取日志的提交范围
CHANGELOG_FILE= # 变更日志文件名称
FORMAT=${FMT_TEXT}   
PREFIX="."    # Git 仓库目录名称前缀 

# --- common functions definition ---
log::info() {
  echo -e "$GRN[INFO]$RST" $@
}
log::warn() {
  echo -e "$YLW[WARN]$RST" $@
}
log::error() {
  echo -e "$RED[FATA]$RST" $@ >&2
  exit 1
}
sys_already_installed() {
  command -v $@ >/dev/null
}

show_help() {
  echo -e "
USAGE
    ${GRN}${PROG}${RST} ${YLW}[--since [VERSION]]${RST} ${YLW}[--until [VERSION]]${RST}

Format git-log message as plain text or markdown table.

OPTIONS
    -f|--format     Output format: text|markdown
    -h|--help)      Print help
    -v|--version)   Print version info
    -p|--prefix)    If provided, search all sub-folders with this prefix. 
                    Otherwise process current directory.
    -s|--since)     Commit id from
    -u|--until)     Commit id to
EXAMPLES
    1. Generate all change logs between 1.0.1 and 1.0.2
    
        \$ $PROG --since 1.0.1 --until 1.0.2

    2. Generate all change logs of version 1.0.2 from the very beginning

        \$ $PROG --until 1.0.2
    
    3. Generate all change logs since version 1.0.2

        \$ $PROG --since 1.0.2
"
  exit 0
}

print_version() {
  echo $VERSION
  exit $?
}

# --- Calculate commit range for git-log ---
validate_parameters() {
  if [ -z "$VERSION_FROM" -a -z "$VERSION_TO" ]; then
    log::error "At least one of these options must be given: ${GRN}--since${RST} or ${GRN}--until${RST}"
  fi

  if [ -z "$VERSION_FROM" ]; then
    COMMIT_RANGE="$VERSION_TO"
    CHANGELOG_FILE="CHANGELOG-${VERSION_TO}.md"
  elif [ -z "$VERSION_TO" ]; then
    COMMIT_RANGE="$VERSION_FROM..HEAD"
    CHANGELOG_FILE="CHANGELOG-${VERSION_FROM}-HEAD.md"
  else
    COMMIT_RANGE="$VERSION_FROM..$VERSION_TO"
    CHANGELOG_FILE="CHANGELOG-${VERSION_FROM}-${VERSION_TO}.md"
  fi

  case $FORMAT in
    "$FMT_TEXT") CHANGELOG_FILE="/dev/stdout";;
    "$FMT_MARKDOWN") ;; # Nothing to do
    *) log::error "You provide wrong format. Valid formats are text or markdown.";;
  esac
}

# --- Print change logs ---
changelog() {
  local repo=$1
  local result=
  
  echo -e "### changelog for git repo: ${GRN}${repo}${RST} ###\n"

  if [[ $FORMAT == $FMT_MARKDOWN ]]; then
    result="$(git log --no-merges --format="| %h | %ad | %an | %s |" --date=short $COMMIT_RANGE 2>/dev/null || true)"
    echo "| COMMIT ID | COMMIT DATE | AUTHOR | COMMIT MSG. |"
    echo "| --- | --- | --- | --- |"
    echo "$result"
  fi

  if [[ $FORMAT == $FMT_TEXT ]]; then
    result="$(git log --no-merges --format="%h %ad %an %s" --date=short $COMMIT_RANGE 2>/dev/null || true)"
    echo "$result" | column -t -l 4 -N "COMMIT ID,DATE,AUTHOR,COMMIT MSG."
  fi
}

subdirs() {
  local pattern=$1
  ls -F | grep -e "^$pattern.*/$" | sed 's /  g'
}

is_git() {
  [ -d ".git" ]
}

# --- Main entrypoint ---
{
  if [ $# -le 0 ]; then
    log::error "No option found. Try '${GRN}${PROG}${RST} ${YLW}--help${RST}' for more details."
  fi

  while [ $# -gt 0 ]; do
    case "$1" in
    -h | --help) show_help ;;
    -v | --version) print_version ;;
    -f | --format)
      FORMAT=$2
      shift 2 || true
      ;;
    -p | --prefix)
      PREFIX=$2
      shift 2 || true
      ;;
    -s | --since)
      VERSION_FROM=$2
      shift 2 || true
      ;;
    -u | --until)
      VERSION_TO=$2
      shift 2 || true
      ;;
    *) log::error "Invalid option '$1'. Try '${GRN}${0}${RST} ${YLW}--help${RST}' for more details." ;;
    esac
  done
  
  log::info "Validating parameters..."
  validate_parameters

  log::info "Changelog will be written to file $CHANGELOG_FILE"
  is_git && changelog `basename "$PWD"` >> "$CHANGELOG_FILE"
  
  if [ ! -z "$PREFIX" ]; then
    for repo in $(subdirs $PREFIX); do
      cd $repo
      if is_git; then
        log::info "appending change logs for $repo ..."
        changelog $repo >> "../$CHANGELOG_FILE"
      fi
      cd ..
    done
  fi
}
