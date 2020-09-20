// ApprovalTests.cpp version v.10.1.2
// More information at: https://github.com/approvals/ApprovalTests.cpp

//----------------------------------------------------------------------
// Welcome to Approval Tests.
//
// If you experience linker errors about missing symbols, it means
// you have forgotten to configure your test framework for Approval Tests.
//
// For help with this, please see:
//     https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md
//----------------------------------------------------------------------

// ******************** From: ApprovalTests.hpp
#ifndef APPROVAL_TESTS_CPP_APPROVALS_HPP
#define APPROVAL_TESTS_CPP_APPROVALS_HPP

// This file is machine-generated. Do not edit.


// ******************** From: ApprovalTestsVersion.h

#define APPROVAL_TESTS_VERSION_MAJOR 10
#define APPROVAL_TESTS_VERSION_MINOR 1
#define APPROVAL_TESTS_VERSION_PATCH 2
#define APPROVAL_TESTS_VERSION_STR "10.1.2"

#define APPROVAL_TESTS_VERSION                                                           \
    (APPROVAL_TESTS_VERSION_MAJOR * 10000 + APPROVAL_TESTS_VERSION_MINOR * 100 +         \
     APPROVAL_TESTS_VERSION_PATCH)

// ******************** From: DiffInfo.h

#include <string>
#include <utility>
#include <vector>

namespace ApprovalTests
{
    enum class Type
    {
        TEXT,
        IMAGE,
        TEXT_AND_IMAGE
    };

    struct DiffInfo
    {
        static std::string receivedFileTemplate();

        static std::string approvedFileTemplate();

        static std::string programFileTemplate();

        static std::string getDefaultArguments();

        DiffInfo(std::string program_, Type type_);

        DiffInfo(std::string program_, std::string arguments_, Type type_);

        std::string program;
        std::string arguments;
        Type type;

        static std::vector<std::string> getProgramFileLocations();

        std::string getProgramForOs() const;
    };
}

// ******************** From: DiffPrograms.h


namespace ApprovalTests
{
    namespace DiffPrograms
    {
        namespace Mac
        {
            DiffInfo DIFF_MERGE();

            DiffInfo ARAXIS_MERGE();

            DiffInfo BEYOND_COMPARE();

            DiffInfo KALEIDOSCOPE();

            DiffInfo SUBLIME_MERGE();

            DiffInfo KDIFF3();

            DiffInfo P4MERGE();

            DiffInfo TK_DIFF();

            DiffInfo VS_CODE();

            DiffInfo CLION();
        }

        namespace Linux
        {
            DiffInfo SUBLIME_MERGE_SNAP();

            DiffInfo SUBLIME_MERGE_FLATPAK();

            DiffInfo SUBLIME_MERGE_REPOSITORY_PACKAGE();

            DiffInfo SUBLIME_MERGE_DIRECT_DOWNLOAD();

            // More ideas available from: https://www.tecmint.com/best-linux-file-diff-tools-comparison/
            DiffInfo KDIFF3();

            DiffInfo MELD();

            DiffInfo BEYOND_COMPARE();
        }

        namespace Windows
        {
            DiffInfo BEYOND_COMPARE_3();

            DiffInfo BEYOND_COMPARE_4();

            DiffInfo TORTOISE_IMAGE_DIFF();

            DiffInfo TORTOISE_TEXT_DIFF();

            DiffInfo TORTOISE_GIT_IMAGE_DIFF();

            DiffInfo TORTOISE_GIT_TEXT_DIFF();

            DiffInfo WIN_MERGE_REPORTER();

            DiffInfo ARAXIS_MERGE();

            DiffInfo CODE_COMPARE();

            DiffInfo SUBLIME_MERGE();

            DiffInfo KDIFF3();

            DiffInfo VS_CODE();
        }
    }
}

// ******************** From: Reporter.h

#include <string>

namespace ApprovalTests
{
    class Reporter
    {
    public:
        virtual ~Reporter() = default;
        virtual bool report(std::string received, std::string approved) const = 0;
    };
}

// ******************** From: ConvertForCygwin.h

#include <string>

namespace ApprovalTests
{
    class ConvertForCygwin
    {
    public:
        virtual ~ConvertForCygwin() = default;

        virtual std::string convertProgramForCygwin(const std::string& filePath);

        virtual std::string convertFileArgumentForCygwin(const std::string& filePath);
    };

    class DoNothing : public ConvertForCygwin
    {
    public:
        std::string convertProgramForCygwin(const std::string& filePath) override;

        std::string convertFileArgumentForCygwin(const std::string& filePath) override;
    };
}

// ******************** From: CommandLauncher.h

#include <string>

namespace ApprovalTests
{
    // An interface to trigger execution of a command. See also SystemLauncher
    class CommandLauncher
    {
    public:
        virtual ~CommandLauncher() = default;
        virtual bool launch(const std::string& commandLine) = 0;
        virtual std::string getCommandLine(const std::string& commandLine) const = 0;
    };
}

// ******************** From: CommandReporter.h

#include <memory>
#include <utility>

namespace ApprovalTests
{
    // Generic reporter to launch arbitrary command
    class CommandReporter : public Reporter
    {
    private:
        std::string cmd;
        std::string arguments = DiffInfo::getDefaultArguments();
        CommandLauncher* l;
        std::shared_ptr<ConvertForCygwin> converter;

        std::string assembleFullCommand(const std::string& received,
                                        const std::string& approved) const;

    protected:
        CommandReporter(std::string command, CommandLauncher* launcher);

        CommandReporter(std::string command, std::string args, CommandLauncher* launcher);

    public:
        static bool exists(const std::string& command);

        bool report(std::string received, std::string approved) const override;

        std::string getCommandLine(const std::string& received,
                                   const std::string& approved) const;

    public:
        void checkForCygwin();

        // Seam for testing
        void useCygwinConversions(bool useCygwin);
    };
}

// ******************** From: ApprovalsMacroDefaults.h

// This file intentionally left blank.

// ******************** From: Macros.h


// Use this in places where we have parameters that are sometimes unused,
// e.g. because of #if
// See https://stackoverflow.com/a/1486931/104370
#define APPROVAL_TESTS_UNUSED(expr)                                                      \
    do                                                                                   \
    {                                                                                    \
        (void)(expr);                                                                    \
    } while (0)

#if __cplusplus >= 201703L
#define APPROVAL_TESTS_NO_DISCARD [[nodiscard]]
#else
#define APPROVAL_TESTS_NO_DISCARD
#endif

#if (__cplusplus >= 201402L)
#define APPROVAL_TESTS_DEPRECATED(text) [[deprecated(text)]]
#define APPROVAL_TESTS_DEPRECATED_CPP11(text)
#else
#define APPROVAL_TESTS_DEPRECATED(text)
#define APPROVAL_TESTS_DEPRECATED_CPP11(text)                                            \
    MoreHelpMessages::deprecatedFunctionCalled(text, __FILE__, __LINE__);
#endif

// ******************** From: WinMinGWUtils.h

#if (defined(__MINGW32__) || defined(__MINGW64__))
#define APPROVAL_TESTS_MINGW
#endif

#ifdef APPROVAL_TESTS_MINGW
#ifdef __cplusplus
extern "C"
{
#endif

#include <sec_api/stdlib_s.h> /* errno_t, size_t */

    errno_t getenv_s(size_t* ret_required_buf_size,
                     char* buf,
                     size_t buf_size_in_bytes,
                     const char* name);

#ifdef __cplusplus
}
#endif

#endif // APPROVAL_TESTS_MINGW

// ******************** From: FileUtils.h

#include <string>

namespace ApprovalTests
{
    class FileUtils
    {
    public:
        static bool fileExists(const std::string& path);

        static int fileSize(const std::string& path);

        static void ensureFileExists(const std::string& fullFilePath);

        static std::string getExtensionWithDot(const std::string& filePath);

        static std::string readFileThrowIfMissing(const std::string& fileName);

        static std::string readFileReturnEmptyIfMissing(const std::string& fileName);

        static void writeToFile(const std::string& filePath, const std::string& content);
    };
}

// ******************** From: StringMaker.h

#include <sstream>
#include <string>

namespace ApprovalTests
{
    class StringMaker
    {
    public:
        template <typename T> static std::string toString(const T& contents)
        {
            std::stringstream s;
            s << contents;
            return s.str();
        }
    };
}

// ******************** From: StringUtils.h




#include <algorithm>
#include <sstream>
#include <string>

namespace ApprovalTests
{
    class StringUtils
    {
    public:
        static std::string replaceAll(std::string inText,
                                      const std::string& find,
                                      const std::string& replaceWith);

        static bool contains(const std::string& inText, const std::string& find);

        static std::string toLower(std::string inText);

        static bool endsWith(std::string value, std::string ending);

        template <typename T> static std::string toString(const T& contents)
        {
            return StringMaker::toString(contents);
        }
    };
}

// ******************** From: SystemUtils.h

#ifdef _WIN32
// ReSharper disable once CppUnusedIncludeDirective
#include <direct.h>
#include <io.h>
#else
// ReSharper disable once CppUnusedIncludeDirective
#include <unistd.h>
#endif


#include <stdexcept>

namespace ApprovalTests
{
    class SystemUtils
    {
    public:
        static bool isWindowsOs();

        static bool isCygwin();

        static bool isMacOs();

        static std::string getDirectorySeparator();

        // Properly cases the filename, but not the directories, on Windows.
        static std::string checkFilenameCase(const std::string& fullPath);

        static std::string safeGetEnvForWindows(char const* name);

        static std::string safeGetEnvForNonWindows(char const* name);

        //! Return the value of the environment variable, or an empty string if the variable is not set.
        static std::string safeGetEnv(char const* name);

        static std::string getMachineName();

        static void makeDirectoryForWindows(const std::string& directory);

        static void makeDirectoryForNonWindows(const std::string& directory);

        static void makeDirectory(const std::string& directory);

        static void ensureDirectoryExists(const std::string& fullFilePath);

        static void runSystemCommandOrThrow(const std::string& command);
    };
}

// ******************** From: SystemLauncher.h


#include <string>

namespace ApprovalTests
{
    class SystemLauncher : public CommandLauncher
    {
    private:
        bool useWindows_ = SystemUtils::isWindowsOs();
        bool isForeground_ = false;

    public:
        explicit SystemLauncher(bool isForeground = false);

        bool launch(const std::string& commandLine) override;

        // Seam for testing
        void invokeForWindows(bool useWindows);

        void setForeground(bool foreground);

        bool isForeground() const;

        std::string getCommandLine(const std::string& commandLine) const override;

        std::string getWindowsCommandLine(const std::string& commandLine,
                                          bool foreground) const;

        std::string getUnixCommandLine(const std::string& commandLine,
                                       bool foreground) const;
    };
}

// ******************** From: GenericDiffReporter.h

#include <string>

namespace ApprovalTests
{
    class GenericDiffReporter : public CommandReporter
    {
    public:
        SystemLauncher launcher;

    public:
        explicit GenericDiffReporter(const std::string& program);

        explicit GenericDiffReporter(const DiffInfo& info);
    };
}

// ******************** From: QuietReporter.h


namespace ApprovalTests
{
    // A reporter that does nothing. Failing tests will still fail, but nothing will be launched.
    class QuietReporter : public Reporter
    {
    public:
        bool report(std::string /*received*/, std::string /*approved*/) const override;
    };
}

// ******************** From: TextDiffReporter.h


#include <memory>

namespace ApprovalTests
{
    // A Reporter class that only uses text-based diff tools, with output written
    // to the console. It provides no opportunity for interactive approving
    // of files.
    // It currently has a short, hard-coded list of diffing tools.
    class TextDiffReporter : public Reporter
    {
    private:
        std::unique_ptr<Reporter> m_reporter;

    public:
        TextDiffReporter();

        bool report(std::string received, std::string approved) const override;
    };
} // namespace ApprovalTests

// ******************** From: Blocker.h

namespace ApprovalTests
{
    class Blocker
    {
    public:
        Blocker() = default;
        Blocker(const Blocker&) = default;
        Blocker(Blocker&&) = default;
        Blocker& operator=(const Blocker&) = default;
        Blocker& operator=(Blocker&&) = default;

        virtual ~Blocker() = default;

        virtual bool isBlockingOnThisMachine() const = 0;
    };
}

// ******************** From: MachineBlocker.h

#include <utility>

namespace ApprovalTests
{
    class MachineBlocker : public Blocker
    {
    private:
        std::string machineName;
        bool block;

        MachineBlocker() = delete;

    public:
        MachineBlocker(std::string machineName_, bool block_);

        static MachineBlocker onMachineNamed(const std::string& machineName);

        static MachineBlocker onMachinesNotNamed(const std::string& machineName);

        virtual bool isBlockingOnThisMachine() const override;
    };
}

// ******************** From: AutoApproveReporter.h


namespace ApprovalTests
{
    class AutoApproveReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override;
    };
}

// ******************** From: ApprovalNamer.h

#include <string>

namespace ApprovalTests
{
    class ApprovalNamer
    {
    public:
        virtual ~ApprovalNamer() = default;
        virtual std::string getApprovedFile(std::string extensionWithDot) const = 0;
        virtual std::string getReceivedFile(std::string extensionWithDot) const = 0;
    };
}

// ******************** From: ApprovalTestNamer.h

#include <stdexcept>
#include <vector>

namespace ApprovalTests
{
    class TestName
    {
    public:
        const std::string& getFileName() const;

        void setFileName(const std::string& file);

    private:
        static void checkBuildConfiguration(const std::string& fileName);

    public:
        static std::string getMisconfiguredBuildHelp(const std::string& fileName);

        std::vector<std::string> sections;

    private:
        std::string fileName;
    };

    class TestConfiguration
    {
    public:
        std::string subdirectory;
    };

    class ApprovalTestNamer : public ApprovalNamer
    {
    private:
    public:
        ApprovalTestNamer() = default;

        std::string getTestName() const;

        static bool isForbidden(char c);

        static std::string convertToFileName(const std::string& fileName);

        static TestName& getCurrentTest();

        static std::string getMisconfiguredMainHelp();

        // Deprecated - please use getSourceFileName
        std::string getFileName() const;

        std::string getSourceFileName() const;

        std::string getDirectory() const;

        static TestName& currentTest(TestName* value = nullptr);

        static TestConfiguration& testConfiguration();

        virtual std::string getApprovedFile(std::string extensionWithDot) const override;

        virtual std::string getReceivedFile(std::string extensionWithDot) const override;

        std::string getOutputFileBaseName() const;

        std::string getFullFileName(const std::string& approved,
                                    const std::string& extensionWithDot) const;
    };
}

// ******************** From: SectionNameDisposer.h


namespace ApprovalTests
{
    class APPROVAL_TESTS_NO_DISCARD SectionNameDisposer
    {
    public:
        SectionNameDisposer(TestName& currentTest_, const std::string& scope_name);

        ~SectionNameDisposer();

    private:
        TestName& currentTest;
    };
}

// ******************** From: GoogleCustomizationsFactory.h


#include <functional>
#include <string>
#include <vector>

namespace ApprovalTests
{
    class GoogleCustomizationsFactory
    {
    public:
        using Comparator = std::function<bool(const std::string&, const std::string&)>;

    private:
        using ComparatorContainer = std::vector<Comparator>;
        static ComparatorContainer& comparatorContainer();

    public:
        static ComparatorContainer getEquivalencyChecks();

        APPROVAL_TESTS_NO_DISCARD static bool
        addTestCaseNameRedundancyCheck(const Comparator& comparator);
    };
}

// ******************** From: FmtToString.h
#ifdef FMT_VERSION
namespace ApprovalTests
{
    class FmtToString
    {
    public:
        template <typename T> static std::string toString(const T& printable)
        {
            (void)printable;
            return fmt::to_string(printable);
        }
    };

}
#endif

// ******************** From: MoreHelpMessages.h

#include <string>

namespace ApprovalTests
{
    class MoreHelpMessages
    {
    public:
        static void deprecatedFunctionCalled(const std::string& message,
                                             const std::string& file,
                                             int lineNumber);
    };
}

// ******************** From: CartesianProduct.h

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace ApprovalTests
{
    namespace CartesianProduct
    {
        namespace Detail
        {

            // C++14 compatibility
            // See https://en.cppreference.com/w/cpp/types/enable_if
            template <bool B, class T = void>
            using enable_if_t = typename std::enable_if<B, T>::type;

            // See https://en.cppreference.com/w/cpp/utility/integer_sequence
            template <std::size_t... Is> struct index_sequence
            {
            };

            template <std::size_t N, std::size_t... Is>
            struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...>
            {
            };

            template <std::size_t... Is>
            struct make_index_sequence<0, Is...> : index_sequence<Is...>
            {
            };
            // End of C++14 compatibility

            // Return the size of a tuple - constexpr for use as a template argument
            // See https://en.cppreference.com/w/cpp/utility/tuple/tuple_size
            template <class Tuple> constexpr std::size_t tuple_size()
            {
                return std::tuple_size<
                    typename std::remove_reference<Tuple>::type>::value;
            }

            template <class Tuple>
            using make_tuple_idxs = make_index_sequence<tuple_size<Tuple>()>;

            // C++17 compatibility
            // See https://en.cppreference.com/w/cpp/utility/apply
            template <class F, class Tuple, std::size_t... I>
            constexpr auto apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
                -> decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...))
            {
                return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
            }

            template <class F, class Tuple>
            auto apply(F&& f, Tuple&& t) -> decltype(apply_impl(std::forward<F>(f),
                                                                std::forward<Tuple>(t),
                                                                make_tuple_idxs<Tuple>{}))
            {
                return apply_impl(
                    std::forward<F>(f), std::forward<Tuple>(t), make_tuple_idxs<Tuple>{});
            }
            // End of C++17 compatibility

            template <class Tuple, class F, std::size_t... Is>
            void for_each_impl(Tuple&& t, F&& f, index_sequence<Is...>)
            {
                (void)std::initializer_list<int>{
                    (std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), 0)...};
            }

            template <class Tuple, class F> void for_each(Tuple&& t, F&& f)
            {
                for_each_impl(
                    std::forward<Tuple>(t), std::forward<F>(f), make_tuple_idxs<Tuple>{});
            }

            template <class Tuple, class F, std::size_t... Is>
            auto transform_impl(Tuple&& t, F&& f, index_sequence<Is...>)
                -> decltype(std::make_tuple(
                    std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t)))...))
            {
                return std::make_tuple(
                    std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t)))...);
            }

            template <class F, class Tuple>
            auto transform(Tuple&& t, F&& f = {})
                -> decltype(transform_impl(std::forward<Tuple>(t),
                                           std::forward<F>(f),
                                           make_tuple_idxs<Tuple>{}))
            {
                return transform_impl(
                    std::forward<Tuple>(t), std::forward<F>(f), make_tuple_idxs<Tuple>{});
            }

            template <class Predicate> struct find_if_body
            {
                const Predicate& pred;
                std::size_t& index;
                std::size_t currentIndex = 0;
                bool found = false;

                find_if_body(const Predicate& p, std::size_t& i) : pred(p), index(i)
                {
                }

                template <typename T> void operator()(T&& value)
                {
                    if (found)
                        return;
                    if (pred(std::forward<T>(value)))
                    {
                        index = currentIndex;
                        found = true;
                    }
                    ++currentIndex;
                }
            };

            template <class Predicate, class Tuple>
            std::size_t find_if(Tuple&& tuple, Predicate pred = {})
            {
                std::size_t idx = tuple_size<Tuple>();
                for_each(std::forward<Tuple>(tuple), find_if_body<Predicate>(pred, idx));
                return idx;
            }

            template <class Predicate, class Tuple>
            bool any_of(Tuple&& tuple, Predicate pred = {})
            {
                return find_if(std::forward<Tuple>(tuple), pred) != tuple_size<Tuple>();
            }

            struct is_range_empty
            {
                template <class T> bool operator()(const T& range) const
                {
                    using std::begin;
                    using std::end;
                    return begin(range) == end(range);
                }
            };

            // Transform an iterator into a value reference which will then be passed to the visitor function:
            struct dereference_iterator
            {
                template <class It>
                auto operator()(It&& it) const -> decltype(*std::forward<It>(it))
                {
                    return *std::forward<It>(it);
                }
            };

            // Increment outermost iterator. If it reaches its end, we're finished and do nothing.
            template <class Its, std::size_t I = tuple_size<Its>() - 1>
            enable_if_t<I == 0> increment_iterator(Its& it, const Its&, const Its&)
            {
                ++std::get<I>(it);
            }

            // Increment inner iterator. If it reaches its end, we reset it and increment the previous iterator.
            template <class Its, std::size_t I = tuple_size<Its>() - 1>
            enable_if_t<I != 0>
            increment_iterator(Its& its, const Its& begins, const Its& ends)
            {
                if (++std::get<I>(its) == std::get<I>(ends))
                {
                    std::get<I>(its) = std::get<I>(begins);
                    increment_iterator<Its, I - 1>(its, begins, ends);
                }
            }
        } // namespace Detail

        // This is what actually loops over all the containers, one element at a time
        // It is called with a template type F that writes the inputs, and runs the converter, which writes the result(s)
        // all for one set of container values - when called by verifyAllCombinations()
        // More generally, F must have an operator() that acts on one set of input values.
        template <class F, class... Ranges>
        void cartesian_product(F&& f, const Ranges&... ranges)
        {
            using std::begin;
            using std::end;

            if (Detail::any_of<Detail::is_range_empty>(std::forward_as_tuple(ranges...)))
                return;

            const auto begins = std::make_tuple(begin(ranges)...);
            const auto ends = std::make_tuple(end(ranges)...);

            for (auto its = begins; std::get<0>(its) != std::get<0>(ends);
                 Detail::increment_iterator(its, begins, ends))
            {
                // Command-clicking on transform in CLion 2019.2.1 hangs with CLion with high CPU
                // 'Use clang tidy' is turned off.
                // Power-save turned on.
                // Mac
                Detail::apply(std::forward<F>(f),
                              Detail::transform<Detail::dereference_iterator>(its));
            }
        }
    } // namespace CartesianProduct
} // namespace ApprovalTests

// ******************** From: DefaultReporter.h


#include <string>

namespace ApprovalTests
{
    class DefaultReporter : public Reporter
    {
    public:
        virtual bool report(std::string received, std::string approved) const override;
    };
}

// ******************** From: ExistingFileNamer.h

#include <utility>

namespace ApprovalTests
{
    class ExistingFileNamer : public ApprovalNamer
    {
        std::string filePath;

    public:
        explicit ExistingFileNamer(std::string filePath_);

        virtual std::string getApprovedFile(std::string extensionWithDot) const override;

        virtual std::string
            getReceivedFile(std::string /*extensionWithDot*/) const override;
    };
}

// ******************** From: ApprovalWriter.h

#include <string>

namespace ApprovalTests
{
    class ApprovalWriter
    {
    public:
        virtual ~ApprovalWriter() = default;
        virtual std::string getFileExtensionWithDot() const = 0;
        virtual void write(std::string path) const = 0;
        virtual void cleanUpReceived(std::string receivedPath) const = 0;
    };
}

// ******************** From: Scrubbers.h

#include <functional>
#include <regex>
#include <string>

namespace ApprovalTests
{
    using Scrubber = std::function<std::string(const std::string&)>;
    namespace Scrubbers
    {
        std::string doNothing(const std::string& input);

        /**@name Regex-based scrubbers

         See \userguide{how_tos/ScrubNonDeterministicOutput,regular-expressions-regex,Regular Expressions (regex)}
         */
        ///@{
        using RegexMatch = std::sub_match<std::string::const_iterator>;
        using RegexReplacer = std::function<std::string(const RegexMatch&)>;

        std::string scrubRegex(const std::string& input,
                               const std::regex& regex,
                               const RegexReplacer& replaceFunction);

        Scrubber createRegexScrubber(const std::regex& regexPattern,
                                     const RegexReplacer& replacer);

        Scrubber createRegexScrubber(const std::regex& regexPattern,
                                     const std::string& replacementText);

        Scrubber createRegexScrubber(const std::string& regexString,
                                     const std::string& replacementText);
        ///@}

        std::string scrubGuid(const std::string& input);
    }
}

// ******************** From: Options.h

#include <exception>
#include <utility>


namespace ApprovalTests
{
    class Options
    {
    public:
        class FileOptions
        {
            const Options* options_ = nullptr; // set in Options::fileOptions()
            std::string fileExtensionWithDot_ = ".txt";
            friend class Options;

            FileOptions() = default;

            explicit FileOptions(std::string fileExtensionWithDot);

            APPROVAL_TESTS_NO_DISCARD
            FileOptions clone() const;

        public:
            APPROVAL_TESTS_NO_DISCARD
            const std::string& getFileExtension() const;

            APPROVAL_TESTS_NO_DISCARD
            Options withFileExtension(const std::string& fileExtensionWithDot) const;
        };

    private:
        FileOptions fileOptions_;
        Scrubber scrubber_ = Scrubbers::doNothing;
        const Reporter& reporter_ = defaultReporter();
        bool usingDefaultScrubber_ = true;

        Options(FileOptions fileOptions,
                Scrubber scrubber,
                const Reporter& reporter,
                bool usingDefaultScrubber);

        APPROVAL_TESTS_NO_DISCARD
        Options clone(const FileOptions& fileOptions) const;

        static const Reporter& defaultReporter();

    public:
        Options() = default;

        explicit Options(Scrubber scrubber);

        explicit Options(const Reporter& reporter);

        APPROVAL_TESTS_NO_DISCARD
        FileOptions fileOptions() const;

        APPROVAL_TESTS_NO_DISCARD
        Scrubber getScrubber() const;

        APPROVAL_TESTS_NO_DISCARD
        bool isUsingDefaultScrubber() const;

        APPROVAL_TESTS_NO_DISCARD
        std::string scrub(const std::string& input) const;

        APPROVAL_TESTS_NO_DISCARD
        const Reporter& getReporter() const;

        APPROVAL_TESTS_NO_DISCARD
        Options withReporter(const Reporter& reporter) const;

        APPROVAL_TESTS_NO_DISCARD
        Options withScrubber(Scrubber scrubber) const;
    };

    namespace Detail
    {
        //! Helper to prevent compilation failure when types are wrongly treated as Option
        //  or Reporter:
        template <typename T, typename R = void>
        using EnableIfNotOptionsOrReporter = typename std::enable_if<
            (!std::is_same<Options, typename std::decay<T>::type>::value) &&
                (!std::is_base_of<Reporter, typename std::decay<T>::type>::value),
            R>::type;
    } // namespace Detail
}

// ******************** From: ExistingFile.h

#include <utility>

namespace ApprovalTests
{
    class ExistingFile : public ApprovalWriter
    {
        std::string filePath;
        bool deleteScrubbedFile = false;

        std::string scrub(std::string fileName, const Options& options);

    public:
        explicit ExistingFile(std::string filePath_, const Options& options);
        virtual std::string getFileExtensionWithDot() const override;
        virtual void write(std::string /*path*/) const override;
        virtual void cleanUpReceived(std::string receivedPath) const override;
        ExistingFileNamer getNamer();
    };
}

// ******************** From: FirstWorkingReporter.h

#include <memory>
#include <vector>

namespace ApprovalTests
{
    class FirstWorkingReporter : public Reporter
    {
    private:
        std::vector<std::shared_ptr<Reporter>> reporters;

    public:
        // Note that FirstWorkingReporter takes ownership of the given Reporter objects
        explicit FirstWorkingReporter(const std::vector<Reporter*>& theReporters);

        explicit FirstWorkingReporter(
            const std::vector<std::shared_ptr<Reporter>>& reporters_);

        bool report(std::string received, std::string approved) const override;
    };
}

// ******************** From: DefaultFrontLoadedReporter.h


namespace ApprovalTests
{
    class DefaultFrontLoadedReporter : public FirstWorkingReporter
    {
    public:
        DefaultFrontLoadedReporter();
    };
}

// ******************** From: FrontLoadedReporterFactory.h


#include <memory>

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsFrontLoadedReporter()
    class FrontLoadedReporterFactory
    {
        static std::shared_ptr<Reporter>& frontLoadedReporter();

    public:
        static std::shared_ptr<Reporter> getFrontLoadedReporter();

        static void setFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter);
    };
}

// ******************** From: FrontLoadedReporterDisposer.h


namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsFrontLoadedReporter()
    class APPROVAL_TESTS_NO_DISCARD FrontLoadedReporterDisposer
    {
    private:
        std::shared_ptr<Reporter> previous_result;

    public:
        explicit FrontLoadedReporterDisposer(const std::shared_ptr<Reporter>& reporter);

        ~FrontLoadedReporterDisposer();
    };
}

// ******************** From: DefaultReporterFactory.h


#include <memory>

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsDefaultReporter()
    class DefaultReporterFactory
    {
    private:
        static std::shared_ptr<Reporter>& defaultReporter();

    public:
        static std::shared_ptr<Reporter> getDefaultReporter();

        static void setDefaultReporter(const std::shared_ptr<Reporter>& reporter);
    };
}

// ******************** From: DefaultReporterDisposer.h


namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsDefaultReporter()
    class APPROVAL_TESTS_NO_DISCARD DefaultReporterDisposer
    {
    private:
        std::shared_ptr<Reporter> previous_result;

    public:
        explicit DefaultReporterDisposer(const std::shared_ptr<Reporter>& reporter);

        ~DefaultReporterDisposer();
    };
}

// ******************** From: SubdirectoryDisposer.h


#include <string>

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useApprovalsSubdirectory()
    class APPROVAL_TESTS_NO_DISCARD SubdirectoryDisposer
    {
    private:
        std::string previous_result;

    public:
        explicit SubdirectoryDisposer(std::string subdirectory);

        ~SubdirectoryDisposer();
    };
}

// ******************** From: DefaultNamerFactory.h


#include <functional>
#include <memory>

namespace ApprovalTests
{

    using NamerCreator = std::function<std::shared_ptr<ApprovalNamer>()>;

    //! Implementation detail of Approvals::useAsDefaultNamer()
    class DefaultNamerFactory
    {
    private:
        static NamerCreator& defaultNamer();

    public:
        static NamerCreator getDefaultNamer();

        static void setDefaultNamer(NamerCreator namer);
    };
}

// ******************** From: DefaultNamerDisposer.h


namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsDefaultNamer()
    class APPROVAL_TESTS_NO_DISCARD DefaultNamerDisposer
    {
    private:
        NamerCreator previous_result;

    public:
        explicit DefaultNamerDisposer(NamerCreator namerCreator);

        ~DefaultNamerDisposer();
    };
}

// ******************** From: StringWriter.h


namespace ApprovalTests
{
    class StringWriter : public ApprovalWriter
    {
    private:
        std::string s;
        std::string ext;

    public:
        explicit StringWriter(std::string contents,
                              std::string fileExtensionWithDot = ".txt");

        std::string getFileExtensionWithDot() const override;

        void write(std::string path) const override;

        void Write(std::ostream& out) const;

        virtual void cleanUpReceived(std::string receivedPath) const override;
    };
}

// ******************** From: ApprovalComparator.h

#include <string>

namespace ApprovalTests
{
    class ApprovalComparator
    {
    public:
        virtual ~ApprovalComparator() = default;

        virtual bool contentsAreEquivalent(std::string receivedPath,
                                           std::string approvedPath) const = 0;
    };
}

// ******************** From: ComparatorDisposer.h

#include <map>
#include <memory>
#include <utility>

namespace ApprovalTests
{

    using ComparatorContainer =
        std::map<std::string, std::shared_ptr<ApprovalComparator>>;

    class APPROVAL_TESTS_NO_DISCARD ComparatorDisposer
    {
    public:
        ComparatorDisposer(
            ComparatorContainer& comparators_,
            const std::string& extensionWithDot,
            std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator_,
            std::shared_ptr<ApprovalTests::ApprovalComparator> newComparator);

        ComparatorDisposer(const ComparatorDisposer&) = delete;

        ComparatorDisposer(ComparatorDisposer&& other) noexcept;

        ~ComparatorDisposer();

    private:
        // A disposer becomes inactive when it is moved from.
        // This is done to prevent a comparator from being disposed twice.
        bool isActive = true;
        ComparatorContainer& comparators;
        std::string ext_;
        std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator;
    };
}

// ******************** From: ComparatorFactory.h

#include <memory>

namespace ApprovalTests
{

    class ComparatorFactory
    {
    private:
        static ComparatorContainer& comparators();

    public:
        static ComparatorDisposer
        registerComparator(const std::string& extensionWithDot,
                           std::shared_ptr<ApprovalComparator> comparator);

        static std::shared_ptr<ApprovalComparator>
        getComparatorForFile(const std::string& receivedPath);

        static std::shared_ptr<ApprovalComparator>
        getComparatorForFileExtensionWithDot(const std::string& fileExtensionWithDot);
    };
}

// ******************** From: FileApprover.h

#include <memory>

namespace ApprovalTests
{
    class FileApprover
    {

    public:
        FileApprover() = default;

        ~FileApprover() = default;

        /*! \brief Register a custom comparater, which will be used to compare approved
         *         and received files with the given extension.
         *
         * @param extensionWithDot A file extention, such as ".jpg"
         * @param comparator <tt>std::shared_ptr</tt> to a ApprovalTests::ApprovalComparator
         *                   instance
         * @return A "Disposable" object. The caller should hold on to this object.
         *         When it is destroyed, the customisation will be reversed.
         *
         * \see For more information, see
         *      \userguide{CustomComparators,Custom Comparators}
         */
        static ComparatorDisposer
        registerComparatorForExtension(const std::string& extensionWithDot,
                                       std::shared_ptr<ApprovalComparator> comparator);

        //! This overload is an implementation detail. To add a new comparator, use registerComparatorForExtension().
        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath,
                           const ApprovalComparator& comparator);

        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath);

        static void
        verify(const ApprovalNamer& n, const ApprovalWriter& s, const Reporter& r);

        static void reportAfterTryingFrontLoadedReporter(const std::string& receivedPath,
                                                         const std::string& approvedPath,
                                                         const Reporter& r);
    };
}

// ******************** From: Approvals.h
#include <exception>
#include <functional>
#include <string>
#include <utility>


namespace ApprovalTests
{

    // TCompileTimeOptions must have a type ToStringConverter, which must have a method toString()
    template <typename TCompileTimeOptions> class TApprovals
    {
    private:
        TApprovals() = default;

        ~TApprovals() = default;

    public:
        static std::shared_ptr<ApprovalNamer> getDefaultNamer()
        {
            return DefaultNamerFactory::getDefaultNamer()();
        }

        template <typename T>
        using IsNotDerivedFromWriter =
            typename std::enable_if<!std::is_base_of<ApprovalWriter, T>::value,
                                    int>::type;

        /**@name Verifying single objects

         See \userguide{TestingSingleObjects,Testing Single Objects}
         */
        ///@{
        static void verify(const std::string& contents,
                           const Options& options = Options())
        {
            StringWriter writer(options.scrub(contents),
                                options.fileOptions().getFileExtension());
            FileApprover::verify(*getDefaultNamer(), writer, options.getReporter());
        }

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        static void verify(const T& contents, const Options& options = Options())
        {
            verify(TCompileTimeOptions::ToStringConverter::toString(contents), options);
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotOptionsOrReporter<Function>>
        static void
        verify(const T& contents, Function converter, const Options& options = Options())
        {
            std::stringstream s;
            converter(contents, s);
            verify(s.str(), options);
        }

        /// Note that this overload ignores any scrubber in options
        static void verify(const ApprovalWriter& writer,
                           const Options& options = Options())
        {
            FileApprover::verify(*getDefaultNamer(), writer, options.getReporter());
        }
        ///@}

        /**@name Verifying containers of objects

         See \userguide{TestingContainers,Testing Containers}
         */
        ///@{
        template <typename Iterator>
        static void verifyAll(
            const std::string& header,
            const Iterator& start,
            const Iterator& finish,
            std::function<void(typename Iterator::value_type, std::ostream&)> converter,
            const Options& options = Options())
        {
            std::stringstream s;
            if (!header.empty())
            {
                s << header << "\n\n\n";
            }
            for (auto it = start; it != finish; ++it)
            {
                converter(*it, s);
                s << '\n';
            }
            verify(s.str(), options);
        }

        template <typename Container>
        static void verifyAll(
            const std::string& header,
            const Container& list,
            std::function<void(typename Container::value_type, std::ostream&)> converter,
            const Options& options = Options())
        {
            verifyAll<typename Container::const_iterator>(
                header, list.begin(), list.end(), converter, options);
        }

        template <typename T>
        static void verifyAll(const std::string& header,
                              const std::vector<T>& list,
                              const Options& options = Options())
        {
            int i = 0;
            verifyAll<std::vector<T>>(
                header,
                list,
                [&](T e, std::ostream& s) {
                    s << "[" << i++
                      << "] = " << TCompileTimeOptions::ToStringConverter::toString(e);
                },
                options);
        }

        template <typename T>
        static void verifyAll(const std::vector<T>& list,
                              const Options& options = Options())
        {
            verifyAll<T>("", list, options);
        }
        ///@}

        /**@name Other verify methods
         */
        ///@{

        /*! \brief Verify the text of an exception

            See \userguide{TestingExceptions,testing-exception-messages,Testing exception messages}
         */
        static void
        verifyExceptionMessage(const std::function<void(void)>& functionThatThrows,
                               const Options& options = Options())
        {
            std::string message = "*** no exception thrown ***";
            try
            {
                functionThatThrows();
            }
            catch (const std::exception& e)
            {
                message = e.what();
            }
            verify(message, options);
        }

        /// Verify an existing file, that has already been written out
        static void verifyExistingFile(const std::string& filePath,
                                       const Options& options = Options())
        {
            ExistingFile writer(filePath, options);
            FileApprover::verify(writer.getNamer(), writer, options.getReporter());
        }
        ///@}

        /**@name Customising Approval Tests

         These static methods customise various aspects
         of Approval Tests behaviour.
         */
        ///@{

        /// See \userguide{Configuration,using-sub-directories-for-approved-files,Using sub-directories for approved files}
        static SubdirectoryDisposer
        useApprovalsSubdirectory(const std::string& subdirectory = "approval_tests")
        {
            return SubdirectoryDisposer(subdirectory);
        }

        /// See \userguide{Reporters,registering-a-default-reporter,Registering a default reporter}
        static DefaultReporterDisposer
        useAsDefaultReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return DefaultReporterDisposer(reporter);
        }

        /// See \userguide{Reporters,front-loaded-reporters,Front Loaded Reporters}
        static FrontLoadedReporterDisposer
        useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return FrontLoadedReporterDisposer(reporter);
        }

        /// See \userguide{Namers,registering-a-custom-namer,Registering a Custom Namer}
        static DefaultNamerDisposer useAsDefaultNamer(NamerCreator namerCreator)
        {
            return DefaultNamerDisposer(std::move(namerCreator));
        }
        ///@}
    };

#ifndef APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER
#define APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER StringMaker
#endif

    // Warning: Do not use CompileTimeOptions directly.
    // This interface is subject to change, as future
    // compile-time options are added.
    template <typename TToString> struct CompileTimeOptions
    {
        using ToStringConverter = TToString;
        // more template types may be added to CompileTimeOptions in future, if we add
        // more flexibility that requires compile-time configuration.
    };

    // Template parameter TToString must have a method toString()
    // This interface will not change, as future compile-time options are added.
    template <typename TToString>
    struct ToStringCompileTimeOptions : CompileTimeOptions<TToString>
    {
    };

    using Approvals =
        TApprovals<ToStringCompileTimeOptions<APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER>>;
}

// ******************** From: CombinationApprovals.h

#include <type_traits>
#include <utility>

namespace ApprovalTests
{
    template <typename TCompileTimeOptions> class TCombinationApprovals
    {
    private:
        // Write out second or subsequent input value, with preceding comma and space
        struct print_input
        {
            std::ostream& out;
            template <class T> void operator()(const T& input)
            {
                out << ", " << TCompileTimeOptions::ToStringConverter::toString(input);
            }
        };

        // Write out one row of output
        template <class Converter> struct serialize
        {
            std::ostream& out;
            Converter converter;
            template <class T, class... Ts> void operator()(T&& input1_, Ts&&... inputs)
            {
                // First value is printed without trailing comma
                out << "(" << TCompileTimeOptions::ToStringConverter::toString(input1_);
                // Remaining values are printed with prefix of a comma
                CartesianProduct::Detail::for_each(std::forward_as_tuple(inputs...),
                                                   print_input{out});
                out << ") => " << converter(input1_, inputs...) << '\n';
            }
        };

    public:
        /**@name Verifying combinations of objects

         See \userguide{TestingCombinations,Testing combinations}
         */
        ///@{
        template <class Converter, class Container, class... Containers>
        static void verifyAllCombinations(const Options& options,
                                          Converter&& converter,
                                          const Container& input0,
                                          const Containers&... inputs)
        {
            std::stringstream s;
            CartesianProduct::cartesian_product(
                serialize<Converter>{s, std::forward<Converter>(converter)},
                input0,
                inputs...);
            Approvals::verify(s.str(), options);
        }

        template <class Converter, class... Containers>
        ApprovalTests::Detail::EnableIfNotOptionsOrReporter<
            Converter> static verifyAllCombinations(Converter&& converter,
                                                    const Containers&... inputs)
        {
            verifyAllCombinations(
                Options(), std::forward<Converter>(converter), inputs...);
        }
        ///@}
    };

    using CombinationApprovals = TCombinationApprovals<
        ToStringCompileTimeOptions<APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER>>;

} // namespace ApprovalTests

// ******************** From: TextFileComparator.h


#include <fstream>

namespace ApprovalTests
{
    class TextFileComparator : public ApprovalComparator
    {
    public:
        static std::ifstream::int_type getNextRelevantCharacter(std::ifstream& astream);

        virtual bool contentsAreEquivalent(std::string receivedPath,
                                           std::string approvedPath) const override;
    };
}

// ******************** From: ApprovalException.h

#include <exception>
#include <string>

namespace ApprovalTests
{
    class ApprovalException : public std::exception
    {
    private:
        std::string message;

    public:
        explicit ApprovalException(const std::string& msg);

        virtual const char* what() const noexcept override;
    };

    class ApprovalMismatchException : public ApprovalException
    {
    private:
        std::string format(const std::string& received, const std::string& approved);

    public:
        ApprovalMismatchException(const std::string& received,
                                  const std::string& approved);
    };

    class ApprovalMissingException : public ApprovalException
    {
    private:
        std::string format(const std::string& file);

    public:
        ApprovalMissingException(const std::string& /*received*/,
                                 const std::string& approved);
    };
}

// ******************** From: CheckFileMacroIsAbsolute.h

// Maintenance note: the following help message must be short, and
// not contain any newline characters, as their display looks messy
// in some compiler outputs.
//
// This static_assert can be disabled by
// defining APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK.
// This can be done on the CMake command line with:
// -DCMAKE_CXX_FLAGS_INIT=-DAPPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK
//
// ApprovalTests will then check the validity of __FILE__
// at run-time instead, for test frameworks that use it to
// detect the source file name.

#ifndef APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK
// clang-format off
static_assert(
    (__FILE__[1] == ':') ||
    (__FILE__[0] == '/'),
"There seems to be a problem with your build configuration, probably with Ninja. "
"Please visit https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md "
"The filename is: "
__FILE__
    // clang-format on
);
#endif // APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK

// ******************** From: BoostTestApprovals.h


#ifdef APPROVALS_BOOSTTEST
#define APPROVAL_TESTS_INCLUDE_CPPS

namespace ApprovalTests
{

    class BoostApprovalListener : public boost::unit_test::test_observer
    {
        ApprovalTests::TestName currentTest;

        void test_unit_start(boost::unit_test::test_unit const& test) override
        {
            std::string path(test.p_file_name.begin(), test.p_file_name.end());
            currentTest.setFileName(path);

            currentTest.sections.push_back(test.p_name);
            ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);
        }

        void test_unit_finish(boost::unit_test::test_unit const& /*test*/,
                              unsigned long) override
        {
            currentTest.sections.pop_back();
        }
    };

    int register_our_listener(BoostApprovalListener& t)
    {
        boost::unit_test::framework::register_observer(t);
        return 1;
    }

    BoostApprovalListener o;
    auto dummy_variable = register_our_listener(o);
}

#endif // APPROVALS_BOOSTTEST

// ******************** From: Catch2Approvals.h



#if defined(APPROVALS_CATCH_EXISTING_MAIN)
#define APPROVALS_CATCH
#define CATCH_CONFIG_RUNNER
#elif defined(APPROVALS_CATCH)
#define CATCH_CONFIG_MAIN
#endif

#ifdef APPROVALS_CATCH
#define APPROVAL_TESTS_INCLUDE_CPPS

#include <catch2/catch.hpp>

//namespace ApprovalTests {
struct Catch2ApprovalListener : Catch::TestEventListenerBase
{
    ApprovalTests::TestName currentTest;
    using TestEventListenerBase::
        TestEventListenerBase; // This using allows us to use all base-class constructors
    virtual void testCaseStarting(Catch::TestCaseInfo const& testInfo) override
    {

        currentTest.setFileName(testInfo.lineInfo.file);
        ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);
    }

    virtual void testCaseEnded(Catch::TestCaseStats const& /*testCaseStats*/) override
    {
        while (!currentTest.sections.empty())
        {
            currentTest.sections.pop_back();
        }
    }

    virtual void sectionStarting(Catch::SectionInfo const& sectionInfo) override
    {
        currentTest.sections.push_back(sectionInfo.name);
    }

    virtual void sectionEnded(Catch::SectionStats const& /*sectionStats*/) override
    {
        currentTest.sections.pop_back();
    }
};
//}
CATCH_REGISTER_LISTENER(Catch2ApprovalListener)

#endif
#ifdef TEST_COMMIT_REVERT_CATCH

//namespace ApprovalTests {
struct Catch2TestCommitRevert : Catch::TestEventListenerBase
{
    using TestEventListenerBase::
        TestEventListenerBase; // This using allows us to use all base-class constructors
    virtual void testRunEnded(Catch::TestRunStats const& testRunStats) override
    {
        bool commit = testRunStats.totals.testCases.allOk();
        std::string message = "r ";
        if (commit)
        {
            std::cout << "git add -A \n";
            std::cout << "git commit -m " << message;
        }
        else
        {
            std::cout << "git clean -fd \n";
            std::cout << "git reset --hard HEAD \n";
        }
    }
};
//}
CATCH_REGISTER_LISTENER(Catch2TestCommitRevert)
#endif

// ******************** From: DocTestApprovals.h


#if defined(APPROVALS_DOCTEST_EXISTING_MAIN)
#define APPROVALS_DOCTEST
#define DOCTEST_CONFIG_IMPLEMENT
#elif defined(APPROVALS_DOCTEST)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#endif

#ifdef APPROVALS_DOCTEST
#define APPROVAL_TESTS_INCLUDE_CPPS

#include <doctest/doctest.h>

namespace ApprovalTests
{
    // anonymous namespace to prevent compiler -Wsubobject-linkage warnings
    // This is OK as this code is only compiled on main()
    namespace
    {
        struct AbstractReporter : doctest::IReporter
        {
            virtual void report_query(const doctest::QueryData&) override
            {
            }
            // called when the whole test run starts
            virtual void test_run_start() override
            {
            }

            // called when the whole test run ends (caching a pointer to the input doesn't make sense here)
            virtual void test_run_end(const doctest::TestRunStats&) override
            {
            }

            // called when a test case is started (safe to cache a pointer to the input)
            virtual void test_case_start(const doctest::TestCaseData&) override
            {
            }

#if 20305 <= DOCTEST_VERSION
            // called when a test case is reentered because of unfinished subcases (safe to cache a pointer to the input)
            virtual void test_case_reenter(const doctest::TestCaseData&) override
            {
            }
#endif

            // called when a test case has ended
            virtual void test_case_end(const doctest::CurrentTestCaseStats&) override
            {
            }

            // called when an exception is thrown from the test case (or it crashes)
            virtual void test_case_exception(const doctest::TestCaseException&) override
            {
            }

            // called whenever a subcase is entered (don't cache pointers to the input)
            virtual void subcase_start(const doctest::SubcaseSignature&) override
            {
            }

            // called whenever a subcase is exited (don't cache pointers to the input)
            virtual void subcase_end() override
            {
            }

            // called for each assert (don't cache pointers to the input)
            virtual void log_assert(const doctest::AssertData&) override
            {
            }

            // called for each message (don't cache pointers to the input)
            virtual void log_message(const doctest::MessageData&) override
            {
            }

            // called when a test case is skipped either because it doesn't pass the filters, has a skip decorator
            // or isn't in the execution range (between first and last) (safe to cache a pointer to the input)
            virtual void test_case_skipped(const doctest::TestCaseData&) override
            {
            }
        };

        struct DocTestApprovalListener : AbstractReporter
        {
            TestName currentTest;

            // constructor has to accept the ContextOptions by ref as a single argument
            explicit DocTestApprovalListener(const doctest::ContextOptions& /*in*/)
            {
            }

            std::string doctestToString(const doctest::String& string) const
            {
                return string.c_str();
            }

            std::string doctestToString(const char* string) const
            {
                return string;
            }

            void test_case_start(const doctest::TestCaseData& testInfo) override
            {
                currentTest.sections.emplace_back(testInfo.m_name);
                currentTest.setFileName(doctestToString(testInfo.m_file));
                ApprovalTestNamer::currentTest(&currentTest);
            }

            void test_case_end(const doctest::CurrentTestCaseStats& /*in*/) override
            {

                while (!currentTest.sections.empty())
                {
                    currentTest.sections.pop_back();
                }
            }

            void subcase_start(const doctest::SubcaseSignature& signature) override
            {
                currentTest.sections.emplace_back(doctestToString(signature.m_name));
            }

            void subcase_end() override
            {

                currentTest.sections.pop_back();
            }
        };
    }
}

REGISTER_LISTENER("approvals", 0, ApprovalTests::DocTestApprovalListener);

#endif // APPROVALS_DOCTEST

// ******************** From: FmtApprovals.h
#ifdef FMT_VERSION
namespace ApprovalTests
{
    using FmtApprovals =
        ApprovalTests::TApprovals<ApprovalTests::ToStringCompileTimeOptions<FmtToString>>;
}
#endif

// ******************** From: GoogleConfiguration.h


namespace ApprovalTests
{
    class GoogleConfiguration
    {
    public:
        // This result is not used, it is only there to allow the method to execute, when this is used outside a function.
        APPROVAL_TESTS_NO_DISCARD static bool addTestCaseNameRedundancyCheck(
            GoogleCustomizationsFactory::Comparator comparator);

        // This result is not used, it is only there to allow the method to execute, when this is used outside a function.
        APPROVAL_TESTS_NO_DISCARD static bool
        addIgnorableTestCaseNameSuffix(std::string suffix);

        static GoogleCustomizationsFactory::Comparator
        createIgnorableTestCaseNameSuffixCheck(const std::string& suffix);
    };
}

// ******************** From: GoogleTestApprovals.h


#ifdef APPROVALS_GOOGLETEST_EXISTING_MAIN
#define APPROVALS_GOOGLETEST
#endif

#ifdef APPROVALS_GOOGLETEST
#define APPROVAL_TESTS_INCLUDE_CPPS

#include <gtest/gtest.h>

namespace ApprovalTests
{
    class GoogleTestListener : public testing::EmptyTestEventListener
    {
        TestName currentTest;

    public:
        bool isDuplicate(std::string testFileNameWithExtension, std::string testCaseName)
        {
            for (auto check : GoogleCustomizationsFactory::getEquivalencyChecks())
            {
                if (check(testFileNameWithExtension, testCaseName))
                {
                    return true;
                }
            }
            return false;
        }

        virtual void OnTestStart(const testing::TestInfo& testInfo) override
        {
            currentTest.setFileName(testInfo.file());
            currentTest.sections = {};
            if (!isDuplicate(currentTest.getFileName(), testInfo.test_case_name()))
            {
                currentTest.sections.emplace_back(testInfo.test_case_name());
            }
            if (!std::string(testInfo.name()).empty())
            {
                currentTest.sections.emplace_back(testInfo.name());
            }

            ApprovalTestNamer::currentTest(&currentTest);
        }
    };

    inline void initializeApprovalTestsForGoogleTests()
    {
        auto& listeners = testing::UnitTest::GetInstance()->listeners();
        listeners.Append(new GoogleTestListener);
    }
}

#ifndef APPROVALS_GOOGLETEST_EXISTING_MAIN
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ApprovalTests::initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
#endif //APPROVALS_GOOGLETEST_EXISTING_MAIN

#endif

// ******************** From: UTApprovals.h


#ifdef APPROVALS_UT
#define APPROVAL_TESTS_INCLUDE_CPPS

#if !(__GNUC__ >= 9 or __clang_major__ >= 9)
#error                                                                                   \
    "The [Boost].UT integration with Approval Tests requires source_location support by the compiler"
#endif

#include <boost/ut.hpp>

namespace ApprovalTests
{
    namespace cfg
    {
        class reporter : public boost::ut::reporter<boost::ut::printer>
        {
        private:
            TestName currentTest;

        public:
            auto on(boost::ut::events::test_begin test_begin) -> void
            {
                std::string name = test_begin.name;
                currentTest.sections.emplace_back(name);
                currentTest.setFileName(test_begin.location.file_name());

                ApprovalTestNamer::currentTest(&currentTest);

                boost::ut::reporter<boost::ut::printer>::on(test_begin);
            }

            auto on(boost::ut::events::test_run test_run) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(test_run);
            }

            auto on(boost::ut::events::test_skip test_skip) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(test_skip);
            }

            auto on(boost::ut::events::test_end test_end) -> void
            {
                while (!currentTest.sections.empty())
                {
                    currentTest.sections.pop_back();
                }
                boost::ut::reporter<boost::ut::printer>::on(test_end);
            }

            template <class TMsg> auto on(boost::ut::events::log<TMsg> log) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(log);
            }

            template <class TExpr>
            auto on(boost::ut::events::assertion_pass<TExpr> location) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(location);
            }

            template <class TExpr>
            auto on(boost::ut::events::assertion_fail<TExpr> fail) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(fail);
            }

            auto on(boost::ut::events::fatal_assertion fatal) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(fatal);
            }

            auto on(boost::ut::events::exception exception) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(exception);
            }

            auto on(boost::ut::events::summary summary) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(summary);
            }
        };
    } // namespace cfg
}

template <>
auto boost::ut::cfg<boost::ut::override> =
    boost::ut::runner<ApprovalTests::cfg::reporter>{};

#endif // APPROVALS_UT

// ******************** From: HelpMessages.h

#include <string>

namespace ApprovalTests
{
    class HelpMessages
    {
    public:
        static std::string getMisconfiguredBuildHelp(const std::string& fileName);

        static std::string getMisconfiguredMainHelp();

        static std::string topAndTailHelpMessage(const std::string& message);
    };
}

// ******************** From: NamerFactory.h


#include <string>

namespace ApprovalTests
{
    struct NamerFactory
    {
        static SectionNameDisposer appendToOutputFilename(const std::string& sectionName);
    };
}

// ******************** From: SeparateApprovedAndReceivedDirectoriesNamer.h


namespace ApprovalTests
{
    class SeparateApprovedAndReceivedDirectoriesNamer : public ApprovalTestNamer
    {
    public:
        virtual ~SeparateApprovedAndReceivedDirectoriesNamer() override = default;

        std::string
        getFullFileNameWithExtraDirectory(const std::string& approved,
                                          const std::string& extensionWithDot) const;

        virtual std::string getApprovedFile(std::string extensionWithDot) const override;

        virtual std::string getReceivedFile(std::string extensionWithDot) const override;

        static DefaultNamerDisposer useAsDefaultNamer();
    };
}

// ******************** From: AutoApproveIfMissingReporter.h


namespace ApprovalTests
{
    class AutoApproveIfMissingReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override;
    };
}

// ******************** From: BlockingReporter.h


#include <memory>
#include <utility>

namespace ApprovalTests
{
    class BlockingReporter : public Reporter
    {
    private:
        std::shared_ptr<Blocker> blocker;

        BlockingReporter() = delete;

    public:
        explicit BlockingReporter(std::shared_ptr<Blocker> blocker_);

        static std::shared_ptr<BlockingReporter>
        onMachineNamed(const std::string& machineName);

        static std::shared_ptr<BlockingReporter>
        onMachinesNotNamed(const std::string& machineName);

        virtual bool report(std::string /*received*/,
                            std::string /*approved*/) const override;
    };
}

// ******************** From: CIBuildOnlyReporter.h


#include <memory>

namespace ApprovalTests
{
    // A reporter which uses the supplied reporter, if called on a supported Continuous Integration system
    class CIBuildOnlyReporter : public Reporter
    {
    private:
        std::shared_ptr<Reporter> m_reporter;

    public:
        explicit CIBuildOnlyReporter(
            std::shared_ptr<Reporter> reporter = std::make_shared<TextDiffReporter>());

        bool report(std::string received, std::string approved) const override;

        static bool isRunningUnderCI();
    };
} // namespace ApprovalTests

// ******************** From: CIBuildOnlyReporterUtils.h


namespace ApprovalTests
{
    namespace CIBuildOnlyReporterUtils
    {
        FrontLoadedReporterDisposer
        useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter);
    }
} // namespace ApprovalTests

// ******************** From: ClipboardReporter.h


#include <string>

namespace ApprovalTests
{
    class ClipboardReporter : public Reporter
    {
    public:
        static std::string getCommandLineFor(const std::string& received,
                                             const std::string& approved,
                                             bool isWindows);

        virtual bool report(std::string received, std::string approved) const override;

        static void copyToClipboard(const std::string& newClipboard);
    };
}

// ******************** From: CombinationReporter.h

#include <memory>
#include <vector>

namespace ApprovalTests
{
    class CombinationReporter : public Reporter
    {
    private:
        std::vector<std::unique_ptr<Reporter>> reporters;

    public:
        // Note that CombinationReporter takes ownership of the given Reporter objects
        explicit CombinationReporter(const std::vector<Reporter*>& theReporters);

        bool report(std::string received, std::string approved) const override;
    };
}

// ******************** From: CustomReporter.h

#include <memory>

namespace ApprovalTests
{
    class CustomReporter
    {
    public:
        static std::shared_ptr<GenericDiffReporter> create(std::string path,
                                                           Type type = Type::TEXT);

        static std::shared_ptr<GenericDiffReporter>
        create(std::string path, std::string arguments, Type type = Type::TEXT);

        static std::shared_ptr<GenericDiffReporter>
        createForegroundReporter(std::string path, Type type = Type::TEXT);

        static std::shared_ptr<GenericDiffReporter> createForegroundReporter(
            std::string path, std::string arguments, Type type = Type::TEXT);
    };
}

// ******************** From: DiffReporter.h


namespace ApprovalTests
{
    class DiffReporter : public FirstWorkingReporter
    {
    public:
        DiffReporter();
    };
}

// ******************** From: LinuxReporters.h


namespace ApprovalTests
{
    namespace Linux
    {
        class SublimeMergeSnapReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeSnapReporter();
        };

        class SublimeMergeFlatpakReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeFlatpakReporter();
        };

        class SublimeMergeRepositoryPackageReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeRepositoryPackageReporter();
        };

        class SublimeMergeDirectDownloadReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeDirectDownloadReporter();
        };

        class SublimeMergeReporter : public FirstWorkingReporter
        {
        public:
            SublimeMergeReporter();
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter();
        };

        class MeldReporter : public GenericDiffReporter
        {
        public:
            MeldReporter();
        };

        class BeyondCompareReporter : public GenericDiffReporter
        {
        public:
            BeyondCompareReporter();
        };

        class LinuxDiffReporter : public FirstWorkingReporter
        {
        public:
            LinuxDiffReporter();
        };
    }
}

// ******************** From: MacReporters.h


namespace ApprovalTests
{
    namespace Mac
    {
        class DiffMergeReporter : public GenericDiffReporter
        {
        public:
            DiffMergeReporter();
        };

        class AraxisMergeReporter : public GenericDiffReporter
        {
        public:
            AraxisMergeReporter();
        };

        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter();
        };

        class BeyondCompareReporter : public GenericDiffReporter
        {
        public:
            BeyondCompareReporter();
        };

        class KaleidoscopeReporter : public GenericDiffReporter
        {
        public:
            KaleidoscopeReporter();
        };

        class SublimeMergeReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeReporter();
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter();
        };

        class P4MergeReporter : public GenericDiffReporter
        {
        public:
            P4MergeReporter();
        };

        class TkDiffReporter : public GenericDiffReporter
        {
        public:
            TkDiffReporter();
        };

        // Note that this will be found on Linux too.
        // See https://github.com/approvals/ApprovalTests.cpp/issues/138 for limitations
        class CLionDiffReporter : public GenericDiffReporter
        {
        public:
            CLionDiffReporter();
        };

        class MacDiffReporter : public FirstWorkingReporter
        {
        public:
            MacDiffReporter();
        };
    }
}

// ******************** From: WindowsReporters.h


namespace ApprovalTests
{
    namespace Windows
    {

        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter();
        };

        // ----------------------- Beyond Compare ----------------------------------
        class BeyondCompare3Reporter : public GenericDiffReporter
        {
        public:
            BeyondCompare3Reporter();
        };

        class BeyondCompare4Reporter : public GenericDiffReporter
        {
        public:
            BeyondCompare4Reporter();
        };

        class BeyondCompareReporter : public FirstWorkingReporter
        {
        public:
            BeyondCompareReporter();
        };

        // ----------------------- Tortoise SVN ------------------------------------
        class TortoiseImageDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseImageDiffReporter();
        };

        class TortoiseTextDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseTextDiffReporter();
        };

        class TortoiseDiffReporter : public FirstWorkingReporter
        {
        public:
            TortoiseDiffReporter();
        };

        // ----------------------- Tortoise Git ------------------------------------
        class TortoiseGitTextDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseGitTextDiffReporter();
        };

        class TortoiseGitImageDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseGitImageDiffReporter();
        };

        class TortoiseGitDiffReporter : public FirstWorkingReporter
        {
        public:
            TortoiseGitDiffReporter();
        };

        // -------------------------------------------------------------------------
        class WinMergeReporter : public GenericDiffReporter
        {
        public:
            WinMergeReporter();
        };

        class AraxisMergeReporter : public GenericDiffReporter
        {
        public:
            AraxisMergeReporter();
        };

        class CodeCompareReporter : public GenericDiffReporter
        {
        public:
            CodeCompareReporter();
        };

        class SublimeMergeReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeReporter();
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter();
        };

        class WindowsDiffReporter : public FirstWorkingReporter
        {
        public:
            WindowsDiffReporter();
        };
    }
}

// ******************** From: ExceptionCollector.h

#include <sstream>
#include <exception>
#include <string>
#include <vector>
#include <functional>

namespace ApprovalTests
{
    class ExceptionCollector
    {
        std::vector<std::string> exceptionMessages;

    public:
        void gather(std::function<void(void)> functionThatThrows);

        ~ExceptionCollector();

        void release();
    };
}

// ******************** From: FileUtilsSystemSpecific.h


namespace ApprovalTests
{
    class FileUtilsSystemSpecific
    {
    public:
        static std::string getCommandLineForCopy(const std::string& source,
                                                 const std::string& destination,
                                                 bool isWindows);

        static void copyFile(const std::string& source, const std::string& destination);
    };
}

#ifdef APPROVAL_TESTS_INCLUDE_CPPS

// ******************** From: ComparatorDisposer.cpp

namespace ApprovalTests
{
    ComparatorDisposer::ComparatorDisposer(
        ComparatorContainer& comparators_,
        const std::string& extensionWithDot,
        std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator_,
        std::shared_ptr<ApprovalTests::ApprovalComparator> newComparator)
        : comparators(comparators_)
        , ext_(extensionWithDot)
        , previousComparator(std::move(previousComparator_))
    {
        comparators_[extensionWithDot] = std::move(newComparator);
    }

    ComparatorDisposer::ComparatorDisposer(ComparatorDisposer&& other) noexcept
        : comparators(other.comparators)
        , ext_(std::move(other.ext_))
        , previousComparator(std::move(other.previousComparator))
    {
        other.isActive = false;
    }

    ComparatorDisposer::~ComparatorDisposer()
    {
        if (isActive)
        {
            comparators[ext_] = previousComparator;
        }
    }
}

// ******************** From: ComparatorFactory.cpp

namespace ApprovalTests
{
    ComparatorContainer& ComparatorFactory::comparators()
    {
        static ComparatorContainer allComparators;
        return allComparators;
    }

    ComparatorDisposer
    ComparatorFactory::registerComparator(const std::string& extensionWithDot,
                                          std::shared_ptr<ApprovalComparator> comparator)
    {
        return ComparatorDisposer(comparators(),
                                  extensionWithDot,
                                  getComparatorForFileExtensionWithDot(extensionWithDot),
                                  comparator);
    }

    std::shared_ptr<ApprovalComparator>
    ComparatorFactory::getComparatorForFile(const std::string& receivedPath)
    {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        return getComparatorForFileExtensionWithDot(fileExtension);
    }

    std::shared_ptr<ApprovalComparator>
    ComparatorFactory::getComparatorForFileExtensionWithDot(
        const std::string& fileExtensionWithDot)
    {
        auto iterator = comparators().find(fileExtensionWithDot);
        if (iterator != comparators().end())
        {
            return iterator->second;
        }
        return std::make_shared<TextFileComparator>();
    }
}

// ******************** From: TextFileComparator.cpp

#include <fstream>

namespace ApprovalTests
{
    std::ifstream::int_type
    TextFileComparator::getNextRelevantCharacter(std::ifstream& astream)
    {
        auto ch = astream.get();
        if (ch == '\r')
        {
            return astream.get();
        }
        else
        {
            return ch;
        }
    }

    bool TextFileComparator::contentsAreEquivalent(std::string receivedPath,
                                                   std::string approvedPath) const
    {
        std::ifstream astream(approvedPath.c_str(), std::ios::binary | std::ifstream::in);
        std::ifstream rstream(receivedPath.c_str(), std::ios::binary | std::ifstream::in);

        while (astream.good() && rstream.good())
        {
            int a = getNextRelevantCharacter(astream);
            int r = getNextRelevantCharacter(rstream);

            if (a != r)
            {
                return false;
            }
        }
        return true;
    }
}

// ******************** From: ApprovalException.cpp

#include <sstream>

namespace ApprovalTests
{
    ApprovalException::ApprovalException(const std::string& msg) : message(msg)
    {
    }

    const char* ApprovalException::what() const noexcept
    {
        return message.c_str();
    }

    std::string ApprovalMismatchException::format(const std::string& received,
                                                  const std::string& approved)
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Received does not match approved \n"
          << "Received : \"" << received << "\" \n"
          << "Approved : \"" << approved << "\"";
        return s.str();
    }

    ApprovalMismatchException::ApprovalMismatchException(const std::string& received,
                                                         const std::string& approved)
        : ApprovalException(format(received, approved))
    {
    }

    std::string ApprovalMissingException::format(const std::string& file)
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Approval File Not Found \n"
          << "File: \"" << file << '"';
        return s.str();
    }

    ApprovalMissingException::ApprovalMissingException(const std::string&,
                                                       const std::string& approved)
        : ApprovalException(format(approved))
    {
    }
}

// ******************** From: FileApprover.cpp

namespace ApprovalTests
{

    ComparatorDisposer FileApprover::registerComparatorForExtension(
        const std::string& extensionWithDot,
        std::shared_ptr<ApprovalComparator> comparator)
    {
        return ComparatorFactory::registerComparator(extensionWithDot, comparator);
    }

    void FileApprover::verify(const std::string& receivedPath,
                              const std::string& approvedPath,
                              const ApprovalComparator& comparator)
    {
        if (!FileUtils::fileExists(approvedPath))
        {
            throw ApprovalMissingException(receivedPath, approvedPath);
        }

        if (!FileUtils::fileExists(receivedPath))
        {
            throw ApprovalMissingException(approvedPath, receivedPath);
        }

        if (!comparator.contentsAreEquivalent(receivedPath, approvedPath))
        {
            throw ApprovalMismatchException(receivedPath, approvedPath);
        }
    }

    void FileApprover::verify(const std::string& receivedPath,
                              const std::string& approvedPath)
    {
        verify(receivedPath,
               approvedPath,
               *ComparatorFactory::getComparatorForFile(receivedPath));
    }

    void FileApprover::verify(const ApprovalNamer& n,
                              const ApprovalWriter& s,
                              const Reporter& r)
    {
        std::string approvedPath = n.getApprovedFile(s.getFileExtensionWithDot());
        std::string receivedPath = n.getReceivedFile(s.getFileExtensionWithDot());
        s.write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.cleanUpReceived(receivedPath);
        }
        catch (const ApprovalException&)
        {
            reportAfterTryingFrontLoadedReporter(receivedPath, approvedPath, r);
            throw;
        }
    }

    void
    FileApprover::reportAfterTryingFrontLoadedReporter(const std::string& receivedPath,
                                                       const std::string& approvedPath,
                                                       const Reporter& r)
    {
        auto tryFirst = FrontLoadedReporterFactory::getFrontLoadedReporter();
        if (!tryFirst->report(receivedPath, approvedPath))
        {
            r.report(receivedPath, approvedPath);
        }
    }
}

// ******************** From: Options.cpp

namespace ApprovalTests
{
    // FileOptions -----------------------------------------------------------------------
    Options::FileOptions::FileOptions(std::string fileExtensionWithDot)
        : fileExtensionWithDot_(std::move(fileExtensionWithDot))
    {
    }

    Options::FileOptions Options::FileOptions::clone() const
    {
        // the returned options_ must be null
        return FileOptions(fileExtensionWithDot_);
    }

    const std::string& Options::FileOptions::getFileExtension() const
    {
        return fileExtensionWithDot_;
    }

    Options
    Options::FileOptions::withFileExtension(const std::string& fileExtensionWithDot) const
    {
        FileOptions newSelf(fileExtensionWithDot);
        return options_->clone(newSelf);
    }

    // Options ---------------------------------------------------------------------------
    Options::Options(Options::FileOptions fileOptions,
                     Scrubber scrubber,
                     const Reporter& reporter,
                     bool usingDefaultScrubber)
        : fileOptions_(std::move(fileOptions))
        , scrubber_(std::move(scrubber))
        , reporter_(reporter)
        , usingDefaultScrubber_(usingDefaultScrubber)
    {
    }

    Options Options::clone(const Options::FileOptions& fileOptions) const
    {
        // TODO error this can retain a previous Options* ???
        return Options(fileOptions, scrubber_, reporter_, usingDefaultScrubber_);
    }

    const Reporter& Options::defaultReporter()
    {
        static DefaultReporter defaultReporter;
        return defaultReporter;
    }

    Options::Options(Scrubber scrubber) : scrubber_(std::move(scrubber))
    {
        usingDefaultScrubber_ = false;
    }

    Options::Options(const Reporter& reporter) : reporter_(reporter)
    {
    }

    Options::FileOptions Options::fileOptions() const
    {
        if (fileOptions_.options_ != nullptr)
        {
            throw std::logic_error(
                "Incorrect assumption: A FileOptions has been re-used");
        }
        FileOptions copy = fileOptions_.clone();
        copy.options_ = this;
        return copy;
    }

    Scrubber Options::getScrubber() const
    {
        return scrubber_;
    }

    bool Options::isUsingDefaultScrubber() const
    {
        return usingDefaultScrubber_;
    }

    std::string Options::scrub(const std::string& input) const
    {
        return scrubber_(input);
    }
    const Reporter& Options::getReporter() const
    {
        return reporter_;
    }

    Options Options::withReporter(const Reporter& reporter) const
    {
        return Options(fileOptions_, scrubber_, reporter, usingDefaultScrubber_);
    }

    Options Options::withScrubber(Scrubber scrubber) const
    {
        return Options(fileOptions_, std::move(scrubber), reporter_, false);
    }
}

// ******************** From: GoogleConfiguration.cpp

namespace ApprovalTests
{
    bool GoogleConfiguration::addTestCaseNameRedundancyCheck(
        GoogleCustomizationsFactory::Comparator comparator)
    {
        return GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(comparator);
    }

    bool GoogleConfiguration::addIgnorableTestCaseNameSuffix(std::string suffix)
    {
        return addTestCaseNameRedundancyCheck(
            createIgnorableTestCaseNameSuffixCheck(suffix));
    }

    GoogleCustomizationsFactory::Comparator
    GoogleConfiguration::createIgnorableTestCaseNameSuffixCheck(const std::string& suffix)
    {
        return [suffix](std::string testFileNameWithExtension, std::string testCaseName) {
            if (testCaseName.length() <= suffix.length() ||
                !StringUtils::endsWith(testCaseName, suffix))
            {
                return false;
            }

            auto withoutSuffix =
                testCaseName.substr(0, testCaseName.length() - suffix.length());
            auto withFileExtension = withoutSuffix + ".";
            return StringUtils::contains(testFileNameWithExtension, withFileExtension);
        };
    }
}

// ******************** From: GoogleCustomizationsFactory.cpp

namespace ApprovalTests
{
    GoogleCustomizationsFactory::ComparatorContainer&
    GoogleCustomizationsFactory::comparatorContainer()
    {
        static ComparatorContainer container;
        if (container.empty())
        {
            auto exactNameMatching = [](const std::string& testFileNameWithExtension,
                                        const std::string& testCaseName) {
                return StringUtils::contains(testFileNameWithExtension,
                                             testCaseName + ".");
            };
            container.push_back(exactNameMatching);
        }
        return container;
    }

    GoogleCustomizationsFactory::ComparatorContainer
    GoogleCustomizationsFactory::getEquivalencyChecks()
    {
        return comparatorContainer();
    }

    bool GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(
        const GoogleCustomizationsFactory::Comparator& comparator)
    {
        comparatorContainer().push_back(comparator);
        return true;
    }
}

// ******************** From: SystemLauncher.cpp

namespace ApprovalTests
{
    SystemLauncher::SystemLauncher(bool isForeground) : isForeground_(isForeground)
    {
    }

    bool SystemLauncher::launch(const std::string& commandLine)
    {
        std::string launch = getCommandLine(commandLine);

        SystemUtils::runSystemCommandOrThrow(launch);
        return true;
    }

    void SystemLauncher::invokeForWindows(bool useWindows)
    {
        useWindows_ = useWindows;
    }

    void SystemLauncher::setForeground(bool foreground)
    {
        isForeground_ = foreground;
    }

    bool SystemLauncher::isForeground() const
    {
        return isForeground_;
    }

    std::string SystemLauncher::getCommandLine(const std::string& commandLine) const
    {
        std::string launch = useWindows_
                                 ? getWindowsCommandLine(commandLine, isForeground_)
                                 : getUnixCommandLine(commandLine, isForeground_);
        return launch;
    }

    std::string SystemLauncher::getWindowsCommandLine(const std::string& commandLine,
                                                      bool foreground) const
    {
        std::string launch = foreground
                                 ? (std::string("cmd /S /C ") + "\"" + commandLine + "\"")
                                 : ("start \"\" " + commandLine);

        return launch;
    }

    std::string SystemLauncher::getUnixCommandLine(const std::string& commandLine,
                                                   bool foreground) const
    {
        std::string launch = foreground ? commandLine : (commandLine + " &");

        return launch;
    }
}

// ******************** From: ApprovalTestNamer.cpp

#include <iostream>

namespace ApprovalTests
{
    const std::string& TestName::getFileName() const
    {
        checkBuildConfiguration(fileName);
        return fileName;
    }

    void TestName::setFileName(const std::string& file)
    {
        fileName = SystemUtils::checkFilenameCase(file);
    }

    void TestName::checkBuildConfiguration(const std::string& fileName)
    {
        if (!FileUtils::fileExists(fileName))
        {
            throw std::runtime_error(getMisconfiguredBuildHelp(fileName));
        }
    }

    std::string TestName::getMisconfiguredBuildHelp(const std::string& fileName)
    {
        return "\n\n" + HelpMessages::getMisconfiguredBuildHelp(fileName) + "\n\n";
    }

    std::string ApprovalTestNamer::getTestName() const
    {
        std::stringstream ext;
        auto test = getCurrentTest();
        for (size_t i = 0; i < test.sections.size(); i++)
        {
            if (0 < i)
            {
                ext << ".";
            }
            ext << test.sections[i];
        }

        return convertToFileName(ext.str());
    }

    bool ApprovalTestNamer::isForbidden(char c)
    {
        static std::string forbiddenChars("\\/:?\"<>|' ");
        return std::string::npos != forbiddenChars.find(c);
    }

    std::string ApprovalTestNamer::convertToFileName(const std::string& fileName)
    {
        std::stringstream result;
        for (auto ch : fileName)
        {
            if (!isForbidden(ch))
            {
                result << ch;
            }
            else
            {
                result << "_";
            }
        }
        return result.str();
    }

    TestName& ApprovalTestNamer::getCurrentTest()
    {
        try
        {
            return currentTest();
        }
        catch (const std::runtime_error&)
        {
            std::string helpMessage = getMisconfiguredMainHelp();
            throw std::runtime_error(helpMessage);
        }
    }

    std::string ApprovalTestNamer::getMisconfiguredMainHelp()
    {
        return "\n\n" + HelpMessages::getMisconfiguredMainHelp() + "\n\n";
    }

    std::string ApprovalTestNamer::getFileName() const
    {
        return getSourceFileName();
    }

    std::string ApprovalTestNamer::getSourceFileName() const
    {
        auto file = getCurrentTest().getFileName();
        auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto end = file.rfind('.');
        auto fileName = file.substr(start, end - start);
        return convertToFileName(fileName);
    }

    std::string ApprovalTestNamer::getDirectory() const
    {
        auto file = getCurrentTest().getFileName();
        auto end = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto directory = file.substr(0, end);
        if (!testConfiguration().subdirectory.empty())
        {
            directory +=
                testConfiguration().subdirectory + SystemUtils::getDirectorySeparator();
            SystemUtils::ensureDirectoryExists(directory);
        }
        return directory;
    }

    TestName& ApprovalTestNamer::currentTest(TestName* value)
    {
        static TestName* staticValue;
        if (value != nullptr)
        {
            staticValue = value;
        }
        if (staticValue == nullptr)
        {
            throw std::runtime_error("The variable in currentTest() is not initialised");
        }
        return *staticValue;
    }

    TestConfiguration& ApprovalTestNamer::testConfiguration()
    {
        static TestConfiguration configuration;
        return configuration;
    }

    std::string ApprovalTestNamer::getApprovedFile(std::string extensionWithDot) const
    {

        return getFullFileName(".approved", extensionWithDot);
    }

    std::string ApprovalTestNamer::getReceivedFile(std::string extensionWithDot) const
    {

        return getFullFileName(".received", extensionWithDot);
    }

    std::string ApprovalTestNamer::getOutputFileBaseName() const
    {
        return getSourceFileName() + "." + getTestName();
    }

    std::string
    ApprovalTestNamer::getFullFileName(const std::string& approved,
                                       const std::string& extensionWithDot) const
    {
        std::stringstream ext;
        ext << getDirectory() << getOutputFileBaseName() << approved << extensionWithDot;
        return ext.str();
    }
}

// ******************** From: DefaultNamerDisposer.cpp

namespace ApprovalTests
{
    DefaultNamerDisposer::DefaultNamerDisposer(NamerCreator namerCreator)
    {
        previous_result = DefaultNamerFactory::getDefaultNamer();
        DefaultNamerFactory::setDefaultNamer(std::move(namerCreator));
    }

    DefaultNamerDisposer::~DefaultNamerDisposer()
    {
        DefaultNamerFactory::setDefaultNamer(previous_result);
    }
}

// ******************** From: DefaultNamerFactory.cpp

namespace ApprovalTests
{
    NamerCreator& DefaultNamerFactory::defaultNamer()
    {
        static NamerCreator namer = []() {
            return std::make_shared<ApprovalTestNamer>();
        };
        return namer;
    }

    NamerCreator DefaultNamerFactory::getDefaultNamer()
    {
        return defaultNamer();
    }

    void DefaultNamerFactory::setDefaultNamer(NamerCreator namer)
    {
        defaultNamer() = std::move(namer);
    }
}

// ******************** From: ExistingFileNamer.cpp

namespace ApprovalTests
{
    ExistingFileNamer::ExistingFileNamer(std::string filePath_)
        : filePath(std::move(filePath_))
    {
    }

    std::string ExistingFileNamer::getApprovedFile(std::string extensionWithDot) const
    {
        return DefaultNamerFactory::getDefaultNamer()()->getApprovedFile(
            extensionWithDot);
    }

    std::string ExistingFileNamer::getReceivedFile(std::string) const
    {
        return filePath;
    }
}

// ******************** From: HelpMessages.cpp

namespace ApprovalTests
{

    std::string HelpMessages::getMisconfiguredBuildHelp(const std::string& fileName)
    {
        std::string helpMessage = R"(* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration.
* We cannot find the test source file at:
*   [fileName]
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
)";
        return StringUtils::replaceAll(
            topAndTailHelpMessage(helpMessage), "[fileName]", fileName);
    }

    std::string HelpMessages::getMisconfiguredMainHelp()
    {
        std::string helpMessage = R"(* Welcome to Approval Tests.
*
* You have forgotten to configure your test framework for Approval Tests.
*
* To do this in Catch, add the following to your main.cpp:
*
*     #define APPROVALS_CATCH
*     #include "ApprovalTests.hpp"
*
* To do this in Google Test, add the following to your main.cpp:
*
*     #define APPROVALS_GOOGLETEST
*     #include "ApprovalTests.hpp"
*
* To do this in doctest, add the following to your main.cpp:
*
*     #define APPROVALS_DOCTEST
*     #include "ApprovalTests.hpp"
*
* To do this in Boost.Test, add the following to your main.cpp:
*
*     #define APPROVALS_BOOSTTEST
*     #include "ApprovalTests.hpp"
*
* To do this in [Boost].UT, add the following to your main.cpp:
*
*     #define APPROVALS_UT
*     #include "ApprovalTests.hpp"
*
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md
)";
        return topAndTailHelpMessage(helpMessage);
    }

    std::string HelpMessages::topAndTailHelpMessage(const std::string& message)
    {
        const std::string lineBreak =
            "**************************************************************"
            "***************";
        const std::string lineBuffer =
            "*                                                             "
            "              *\n";
        return lineBreak + '\n' + lineBuffer + message + lineBuffer + lineBreak;
    }
}

// ******************** From: NamerFactory.cpp

namespace ApprovalTests
{
    SectionNameDisposer
    NamerFactory::appendToOutputFilename(const std::string& sectionName)
    {
        return SectionNameDisposer(ApprovalTestNamer::currentTest(), sectionName);
    }
}

// ******************** From: SectionNameDisposer.cpp

namespace ApprovalTests
{
    SectionNameDisposer::SectionNameDisposer(TestName& currentTest_,
                                             const std::string& scope_name)
        : currentTest(currentTest_)
    {
        // Add extra section to output filename, to allow multiple files
        // to verified from a single test:
        currentTest_.sections.push_back(scope_name);
    }

    SectionNameDisposer::~SectionNameDisposer()
    {
        // Remove the extra section we added in the constructor
        currentTest.sections.pop_back();
    }
}

// ******************** From: SeparateApprovedAndReceivedDirectoriesNamer.cpp

namespace ApprovalTests
{
    std::string
    SeparateApprovedAndReceivedDirectoriesNamer::getFullFileNameWithExtraDirectory(
        const std::string& approved, const std::string& extensionWithDot) const
    {
        std::string outputDirectory = getDirectory() + approved;
        SystemUtils::ensureDirectoryExists(outputDirectory);

        std::string outputFile = getFileName() + "." + getTestName() + extensionWithDot;

        return outputDirectory + SystemUtils::getDirectorySeparator() + outputFile;
    }

    std::string SeparateApprovedAndReceivedDirectoriesNamer::getApprovedFile(
        std::string extensionWithDot) const
    {
        return getFullFileNameWithExtraDirectory("approved", extensionWithDot);
    }

    std::string SeparateApprovedAndReceivedDirectoriesNamer::getReceivedFile(
        std::string extensionWithDot) const
    {
        return getFullFileNameWithExtraDirectory("received", extensionWithDot);
    }

    DefaultNamerDisposer SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer()
    {
        return Approvals::useAsDefaultNamer([]() {
            return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();
        });
    }
}

// ******************** From: SubdirectoryDisposer.cpp

namespace ApprovalTests
{
    SubdirectoryDisposer::SubdirectoryDisposer(std::string subdirectory)
    {
        previous_result = ApprovalTestNamer::testConfiguration().subdirectory;
        ApprovalTestNamer::testConfiguration().subdirectory = std::move(subdirectory);
    }

    SubdirectoryDisposer::~SubdirectoryDisposer()
    {
        ApprovalTestNamer::testConfiguration().subdirectory = previous_result;
    }
}

// ******************** From: AutoApproveIfMissingReporter.cpp

namespace ApprovalTests
{
    bool AutoApproveIfMissingReporter::report(std::string received,
                                              std::string approved) const
    {
        if (FileUtils::fileExists(approved))
        {
            return false;
        }

        return AutoApproveReporter().report(received, approved);
    }
}

// ******************** From: AutoApproveReporter.cpp

#include <iostream>

namespace ApprovalTests
{
    bool AutoApproveReporter::report(std::string received, std::string approved) const
    {
        std::cout << "file " << approved
                  << " automatically approved - next run should succeed\n";
        FileUtilsSystemSpecific::copyFile(received, approved);
        return true;
    }
}

// ******************** From: BlockingReporter.cpp

namespace ApprovalTests
{
    BlockingReporter::BlockingReporter(std::shared_ptr<Blocker> blocker_)
        : blocker(std::move(blocker_))
    {
    }

    std::shared_ptr<BlockingReporter>
    BlockingReporter::onMachineNamed(const std::string& machineName)
    {
        auto machineBlocker =
            std::make_shared<MachineBlocker>(MachineBlocker::onMachineNamed(machineName));
        return std::make_shared<BlockingReporter>(machineBlocker);
    }

    std::shared_ptr<BlockingReporter>
    BlockingReporter::onMachinesNotNamed(const std::string& machineName)
    {
        auto machineBlocker = std::make_shared<MachineBlocker>(
            MachineBlocker::onMachinesNotNamed(machineName));
        return std::make_shared<BlockingReporter>(machineBlocker);
    }

    bool BlockingReporter::report(std::string, std::string) const
    {
        return blocker->isBlockingOnThisMachine();
    }
}

// ******************** From: CIBuildOnlyReporter.cpp

namespace ApprovalTests
{
    CIBuildOnlyReporter::CIBuildOnlyReporter(std::shared_ptr<Reporter> reporter)
        : m_reporter(reporter)
    {
    }

    bool CIBuildOnlyReporter::report(std::string received, std::string approved) const
    {
        if (!isRunningUnderCI())
        {
            return false;
        }
        m_reporter->report(received, approved);
        // Return true regardless of whether our report succeeded or not,
        // so that no later reporters run.
        return true;
    }

    bool CIBuildOnlyReporter::isRunningUnderCI()
    {
        /*
        auto AppVeyor = {"CI", "APPVEYOR"}; // https://www.appveyor.com/docs/environment-variables/
        auto AzurePipelines = {"TF_BUILD"}; // https://docs.microsoft.com/en-us/azure/devops/pipelines/build/variables?view=azure-devops&viewFallbackFrom=vsts&tabs=yaml
        auto GitHubActions = {"GITHUB_ACTIONS"}; // https://help.github.com/en/actions/configuring-and-managing-workflows/using-environment-variables
        auto GoCD = {"GO_SERVER_URL"}: // https://docs.gocd.org/current/faq/dev_use_current_revision_in_build.html
        auto Jenkins = {"JENKINS_URL"}: // https://wiki.jenkins.io/display/JENKINS/Building+a+software+project
        auto TeamCity = {"TEAMCITY_VERSION"}; // https://confluence.jetbrains.com/display/TCD18/Predefined+Build+Parameters
        auto Travis = {"CI", "TRAVIS", "CONTINUOUS_INTEGRATION"}; // https://docs.travis-ci.com/user/environment-variables/#default-environment-variables
        auto environmentVariablesForCI = combine({
            AppVeyor,
            AzurePipelines,
            GitHubActions,
            GoCD
            Jenkins,
            TeamCity,
            Travis,
        });
         */
        auto environmentVariablesForCI = {
            "CI",
            "CONTINUOUS_INTEGRATION",
            "GITHUB_ACTIONS",
            "GO_SERVER_URL",
            "JENKINS_URL",
            "TEAMCITY_VERSION",
            "TF_BUILD"
        };
        for (const auto& variable : environmentVariablesForCI)
        {
            if (!SystemUtils::safeGetEnv(variable).empty())
            {
                return true;
            }
        }
        return false;
    }
}

// ******************** From: CIBuildOnlyReporterUtils.cpp

namespace ApprovalTests
{
    FrontLoadedReporterDisposer CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
        const std::shared_ptr<Reporter>& reporter)
    {
        return Approvals::useAsFrontLoadedReporter(
            std::make_shared<ApprovalTests::CIBuildOnlyReporter>(reporter));
    }
}

// ******************** From: ClipboardReporter.cpp

namespace ApprovalTests
{
    std::string ClipboardReporter::getCommandLineFor(const std::string& received,
                                                     const std::string& approved,
                                                     bool isWindows)
    {
        if (isWindows)
        {
            return std::string("move /Y ") + "\"" + received + "\" \"" + approved + "\"";
        }
        else
        {
            return std::string("mv ") + "\"" + received + "\" \"" + approved + "\"";
        }
    }

    bool ClipboardReporter::report(std::string received, std::string approved) const
    {
        copyToClipboard(
            getCommandLineFor(received, approved, SystemUtils::isWindowsOs()));
        return true;
    }

    void ClipboardReporter::copyToClipboard(const std::string& newClipboard)
    {
        /*
     This will probably not work on Linux.

     From https://stackoverflow.com/a/750466/104370
     In case of X, yes, there's xclip (and others). xclip -selection c will send data to the clipboard that
     works with Ctrl-C, Ctrl-V in most applications.

     If you're trying to talk to the Mac OS X clipboard, there's pbcopy.

     If you're in Linux terminal mode (no X) then maybe you need to look into gpm.

     There's also GNU screen which has a clipboard. To put stuff in there, look at the screen command "readreg".

     Under Windows/cygwin, use /dev/clipboard or clip for newer versions of Windows (at least Windows 10).
     */

        std::string clipboardCommand;
        if (SystemUtils::isWindowsOs())
        {
            clipboardCommand = "clip";
        }
        else if (SystemUtils::isMacOs())
        {
            clipboardCommand = "pbcopy";
        }
        else
        {
            clipboardCommand = "pbclip";
        }
        auto cmd = std::string("echo ") + newClipboard + " | " + clipboardCommand;
        SystemUtils::runSystemCommandOrThrow(cmd);
    }
}

// ******************** From: CombinationReporter.cpp

namespace ApprovalTests
{
    CombinationReporter::CombinationReporter(const std::vector<Reporter*>& theReporters)
    {
        for (auto r : theReporters)
        {
            reporters.push_back(std::unique_ptr<Reporter>(r));
        }
    }

    bool CombinationReporter::report(std::string received, std::string approved) const
    {
        bool result = false;
        for (auto& r : reporters)
        {
            result |= r->report(received, approved);
        }
        return result;
    }
}

// ******************** From: CommandReporter.cpp

namespace ApprovalTests
{
    std::string CommandReporter::assembleFullCommand(const std::string& received,
                                                     const std::string& approved) const
    {
        auto convertedCommand = '"' + converter->convertProgramForCygwin(cmd) + '"';
        auto convertedReceived =
            '"' + converter->convertFileArgumentForCygwin(received) + '"';
        auto convertedApproved =
            '"' + converter->convertFileArgumentForCygwin(approved) + '"';

        std::string args;
        args = StringUtils::replaceAll(
            arguments, DiffInfo::receivedFileTemplate(), convertedReceived);
        args = StringUtils::replaceAll(
            args, DiffInfo::approvedFileTemplate(), convertedApproved);

        return convertedCommand + ' ' + args;
    }

    CommandReporter::CommandReporter(std::string command, CommandLauncher* launcher)
        : cmd(std::move(command)), l(launcher)
    {
        checkForCygwin();
    }

    CommandReporter::CommandReporter(std::string command,
                                     std::string args,
                                     CommandLauncher* launcher)
        : cmd(std::move(command)), arguments(std::move(args)), l(launcher)
    {
        checkForCygwin();
    }

    bool CommandReporter::exists(const std::string& command)
    {
        bool foundByWhich = false;
        if (!SystemUtils::isWindowsOs())
        {
            std::string which = "which " + command + " > /dev/null 2>&1";
            int result = system(which.c_str());
            foundByWhich = (result == 0);
        }
        return foundByWhich || FileUtils::fileExists(command);
    }

    bool CommandReporter::report(std::string received, std::string approved) const
    {
        if (!exists(cmd))
        {
            return false;
        }
        FileUtils::ensureFileExists(approved);
        return l->launch(assembleFullCommand(received, approved));
    }

    std::string CommandReporter::getCommandLine(const std::string& received,
                                                const std::string& approved) const
    {
        return l->getCommandLine(assembleFullCommand(received, approved));
    }

    void CommandReporter::checkForCygwin()
    {
        useCygwinConversions(SystemUtils::isCygwin());
    }

    void CommandReporter::useCygwinConversions(bool useCygwin)
    {
        if (useCygwin)
        {
            converter = std::make_shared<ConvertForCygwin>();
        }
        else
        {
            converter = std::make_shared<DoNothing>();
        }
    }
}

// ******************** From: ConvertForCygwin.cpp

namespace ApprovalTests
{
    std::string ConvertForCygwin::convertProgramForCygwin(const std::string& filePath)
    {
        return "$(cygpath '" + filePath + "')";
    }

    std::string
    ConvertForCygwin::convertFileArgumentForCygwin(const std::string& filePath)
    {
        return "$(cygpath -aw '" + filePath + "')";
    }

    std::string DoNothing::convertProgramForCygwin(const std::string& filePath)
    {
        return filePath;
    }

    std::string DoNothing::convertFileArgumentForCygwin(const std::string& filePath)
    {
        return filePath;
    }
}

// ******************** From: CustomReporter.cpp

namespace ApprovalTests
{
    std::shared_ptr<GenericDiffReporter> CustomReporter::create(std::string path,
                                                                Type type)
    {
        return create(std::move(path), DiffInfo::getDefaultArguments(), type);
    }

    std::shared_ptr<GenericDiffReporter>
    CustomReporter::create(std::string path, std::string arguments, Type type)
    {
        DiffInfo info(std::move(path), std::move(arguments), type);
        return std::make_shared<GenericDiffReporter>(info);
    }

    std::shared_ptr<GenericDiffReporter>
    CustomReporter::createForegroundReporter(std::string path, Type type)
    {
        return createForegroundReporter(
            std::move(path), DiffInfo::getDefaultArguments(), type);
    }

    std::shared_ptr<GenericDiffReporter> CustomReporter::createForegroundReporter(
        std::string path, std::string arguments, Type type)
    {
        DiffInfo info(std::move(path), std::move(arguments), type);
        auto reporter = std::make_shared<GenericDiffReporter>(info);
        reporter->launcher.setForeground(true);
        return reporter;
    }
}

// ******************** From: DefaultFrontLoadedReporter.cpp

namespace ApprovalTests
{
    DefaultFrontLoadedReporter::DefaultFrontLoadedReporter()
        : FirstWorkingReporter({new CIBuildOnlyReporter()})
    {
    }
}

// ******************** From: DefaultReporter.cpp

namespace ApprovalTests
{
    bool DefaultReporter::report(std::string received, std::string approved) const
    {
        return DefaultReporterFactory::getDefaultReporter()->report(received, approved);
    }
}

// ******************** From: DefaultReporterDisposer.cpp

namespace ApprovalTests
{
    DefaultReporterDisposer::DefaultReporterDisposer(
        const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = DefaultReporterFactory::getDefaultReporter();
        DefaultReporterFactory::setDefaultReporter(reporter);
    }

    DefaultReporterDisposer::~DefaultReporterDisposer()
    {
        DefaultReporterFactory::setDefaultReporter(previous_result);
    }
}

// ******************** From: DefaultReporterFactory.cpp

namespace ApprovalTests
{
    std::shared_ptr<Reporter>& DefaultReporterFactory::defaultReporter()
    {
        static std::shared_ptr<Reporter> reporter = std::make_shared<DiffReporter>();
        return reporter;
    }

    std::shared_ptr<Reporter> DefaultReporterFactory::getDefaultReporter()
    {
        return defaultReporter();
    }

    void
    DefaultReporterFactory::setDefaultReporter(const std::shared_ptr<Reporter>& reporter)
    {
        defaultReporter() = reporter;
    }
}

// ******************** From: DiffInfo.cpp

namespace ApprovalTests
{
    std::string DiffInfo::receivedFileTemplate()
    {
        return "{Received}";
    }

    std::string DiffInfo::approvedFileTemplate()
    {
        return "{Approved}";
    }

    std::string DiffInfo::programFileTemplate()
    {
        return "{ProgramFiles}";
    }

    std::string DiffInfo::getDefaultArguments()
    {
        return receivedFileTemplate() + ' ' + approvedFileTemplate();
    }

    DiffInfo::DiffInfo(std::string program_, Type type_)
        : program(std::move(program_)), arguments(getDefaultArguments()), type(type_)
    {
    }

    DiffInfo::DiffInfo(std::string program_, std::string arguments_, Type type_)
        : program(std::move(program_)), arguments(std::move(arguments_)), type(type_)
    {
    }

    std::vector<std::string> DiffInfo::getProgramFileLocations()
    {
        std::vector<std::string> possibleWindowsPaths;
        const std::vector<const char*> envVars = {
            "ProgramFiles", "ProgramW6432", "ProgramFiles(x86)"};

        for (const auto& envVar : envVars)
        {
            std::string envVarValue = SystemUtils::safeGetEnv(envVar);
            if (!envVarValue.empty())
            {
                envVarValue += '\\';
                possibleWindowsPaths.push_back(envVarValue);
            }
        }
        return possibleWindowsPaths;
    }

    std::string DiffInfo::getProgramForOs() const
    {
        std::string result = program;
        if (result.rfind(programFileTemplate(), 0) == 0)
        {
            std::vector<std::string> possibleWindowsPaths = getProgramFileLocations();
            for (const auto& path : possibleWindowsPaths)
            {
                auto result1 =
                    StringUtils::replaceAll(result, programFileTemplate(), path);
                if (FileUtils::fileExists(result1))
                {
                    return result1;
                }
            }
        }
        return result;
    }
}

// ******************** From: DiffPrograms.cpp

///////////////////////////////////////////////////////////////////////////////
#define APPROVAL_TESTS_MACROS_ENTRY(name, defaultValue)                                  \
    DiffInfo name()                                                                      \
    {                                                                                    \
        return defaultValue;                                                             \
    }
///////////////////////////////////////////////////////////////////////////////

namespace ApprovalTests
{
    namespace DiffPrograms
    {

        namespace Mac
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                DIFF_MERGE,
                DiffInfo("/Applications/DiffMerge.app/Contents/MacOS/DiffMerge",
                         "{Received} {Approved} -nosplash",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                ARAXIS_MERGE,
                DiffInfo("/Applications/Araxis Merge.app/Contents/Utilities/compare",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                BEYOND_COMPARE,
                DiffInfo("/Applications/Beyond Compare.app/Contents/MacOS/bcomp",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                KALEIDOSCOPE,
                DiffInfo("/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE,
                DiffInfo("/Applications/Sublime "
                         "Merge.app/Contents/SharedSupport/bin/smerge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                KDIFF3,
                DiffInfo("/Applications/kdiff3.app/Contents/MacOS/kdiff3",
                         "{Received} {Approved} -m",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                P4MERGE,
                DiffInfo("/Applications/p4merge.app/Contents/MacOS/p4merge",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TK_DIFF,
                DiffInfo("/Applications/TkDiff.app/Contents/MacOS/tkdiff", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                VS_CODE,
                DiffInfo("/Applications/Visual Studio "
                         "Code.app/Contents/Resources/app/bin/code",
                         "-d {Received} {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(CLION,
                                        DiffInfo("clion",
                                                 "nosplash diff {Received} {Approved}",
                                                 Type::TEXT))
        }

        namespace Linux
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_SNAP,
                DiffInfo("/snap/bin/sublime-merge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_FLATPAK,
                DiffInfo("/var/lib/flatpak/exports/bin/com.sublimemerge.App",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_REPOSITORY_PACKAGE,
                DiffInfo("smerge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_DIRECT_DOWNLOAD,
                DiffInfo("/opt/sublime_merge/sublime_merge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            // More ideas available from: https://www.tecmint.com/best-linux-file-diff-tools-comparison/
            APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("kdiff3", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(MELD, DiffInfo("meld", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE,
                                        DiffInfo("bcompare", Type::TEXT_AND_IMAGE))
        }

        namespace Windows
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                BEYOND_COMPARE_3,
                DiffInfo("{ProgramFiles}Beyond Compare 3\\BCompare.exe",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                BEYOND_COMPARE_4,
                DiffInfo("{ProgramFiles}Beyond Compare 4\\BCompare.exe",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_IMAGE_DIFF,
                DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseIDiff.exe",
                         "/left:{Received} /right:{Approved}",
                         Type::IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_TEXT_DIFF,
                DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseMerge.exe", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_GIT_IMAGE_DIFF,
                DiffInfo("{ProgramFiles}TortoiseGit\\bin\\TortoiseGitIDiff.exe",
                         "/left:{Received} /right:{Approved}",
                         Type::IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_GIT_TEXT_DIFF,
                DiffInfo("{ProgramFiles}TortoiseGit\\bin\\TortoiseGitMerge.exe",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(WIN_MERGE_REPORTER,
                                        DiffInfo("{ProgramFiles}WinMerge\\WinMergeU.exe",
                                                 Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                ARAXIS_MERGE,
                DiffInfo("{ProgramFiles}Araxis\\Araxis Merge\\Compare.exe",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                CODE_COMPARE,
                DiffInfo("{ProgramFiles}Devart\\Code Compare\\CodeCompare.exe",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE,
                DiffInfo("{ProgramFiles}Sublime Merge\\smerge.exe",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(KDIFF3,
                                        DiffInfo("{ProgramFiles}KDiff3\\kdiff3.exe",
                                                 Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                VS_CODE,
                DiffInfo("{ProgramFiles}Microsoft VS Code\\Code.exe",
                         "-d {Received} {Approved}",
                         Type::TEXT))
        }

    }
}

// ******************** From: DiffReporter.cpp


namespace ApprovalTests
{
    DiffReporter::DiffReporter()
        : FirstWorkingReporter({new Mac::MacDiffReporter(),
                                new Linux::LinuxDiffReporter(),
                                new Windows::WindowsDiffReporter()})
    {
    }
}

// ******************** From: FirstWorkingReporter.cpp

namespace ApprovalTests
{
    FirstWorkingReporter::FirstWorkingReporter(const std::vector<Reporter*>& theReporters)
    {
        for (auto r : theReporters)
        {
            reporters.push_back(std::shared_ptr<Reporter>(r));
        }
    }

    FirstWorkingReporter::FirstWorkingReporter(
        const std::vector<std::shared_ptr<Reporter>>& reporters_)
    {
        this->reporters = reporters_;
    }

    bool FirstWorkingReporter::report(std::string received, std::string approved) const
    {
        for (auto& r : reporters)
        {
            if (r->report(received, approved))
            {
                return true;
            }
        }
        return false;
    }
}

// ******************** From: FrontLoadedReporterDisposer.cpp

namespace ApprovalTests
{
    FrontLoadedReporterDisposer::FrontLoadedReporterDisposer(
        const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = FrontLoadedReporterFactory::getFrontLoadedReporter();
        FrontLoadedReporterFactory::setFrontLoadedReporter(reporter);
    }

    FrontLoadedReporterDisposer::~FrontLoadedReporterDisposer()
    {
        FrontLoadedReporterFactory::setFrontLoadedReporter(previous_result);
    }
}

// ******************** From: FrontLoadedReporterFactory.cpp

namespace ApprovalTests
{
    std::shared_ptr<Reporter>& FrontLoadedReporterFactory::frontLoadedReporter()
    {
        static std::shared_ptr<Reporter> reporter =
            std::make_shared<DefaultFrontLoadedReporter>();
        return reporter;
    }

    std::shared_ptr<Reporter> FrontLoadedReporterFactory::getFrontLoadedReporter()
    {
        return frontLoadedReporter();
    }

    void FrontLoadedReporterFactory::setFrontLoadedReporter(
        const std::shared_ptr<Reporter>& reporter)
    {
        frontLoadedReporter() = reporter;
    }
}

// ******************** From: GenericDiffReporter.cpp

namespace ApprovalTests
{
    GenericDiffReporter::GenericDiffReporter(const std::string& program)
        : CommandReporter(program, &launcher)
    {
    }

    GenericDiffReporter::GenericDiffReporter(const DiffInfo& info)
        : CommandReporter(info.getProgramForOs(), info.arguments, &launcher)
    {
    }
}

// ******************** From: LinuxReporters.cpp

namespace ApprovalTests
{
    namespace Linux
    {
        SublimeMergeSnapReporter::SublimeMergeSnapReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_SNAP())
        {
            launcher.setForeground(true);
        }

        SublimeMergeFlatpakReporter::SublimeMergeFlatpakReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_FLATPAK())
        {
            launcher.setForeground(true);
        }

        SublimeMergeRepositoryPackageReporter::SublimeMergeRepositoryPackageReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_REPOSITORY_PACKAGE())
        {
            launcher.setForeground(true);
        }

        SublimeMergeDirectDownloadReporter::SublimeMergeDirectDownloadReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_DIRECT_DOWNLOAD())
        {
            launcher.setForeground(true);
        }

        SublimeMergeReporter::SublimeMergeReporter()
            : FirstWorkingReporter({new SublimeMergeSnapReporter(),
                                    new SublimeMergeFlatpakReporter(),
                                    new SublimeMergeRepositoryPackageReporter(),
                                    new SublimeMergeDirectDownloadReporter()})
        {
        }

        KDiff3Reporter::KDiff3Reporter()
            : GenericDiffReporter(DiffPrograms::Linux::KDIFF3())
        {
        }

        MeldReporter::MeldReporter() : GenericDiffReporter(DiffPrograms::Linux::MELD())
        {
        }

        BeyondCompareReporter::BeyondCompareReporter()
            : GenericDiffReporter(DiffPrograms::Linux::BEYOND_COMPARE())
        {
        }

        LinuxDiffReporter::LinuxDiffReporter()
            : FirstWorkingReporter({
                  new BeyondCompareReporter(),
                  new MeldReporter(),
                  new SublimeMergeReporter(),
                  new KDiff3Reporter()
                  // Note: ApprovalTests::Mac::CLionDiffReporter also works on Linux
              })
        {
        }
    }
}

// ******************** From: MacReporters.cpp


namespace ApprovalTests
{
    namespace Mac
    {
        DiffMergeReporter::DiffMergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::DIFF_MERGE())
        {
        }

        AraxisMergeReporter::AraxisMergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::ARAXIS_MERGE())
        {
        }

        VisualStudioCodeReporter::VisualStudioCodeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::VS_CODE())
        {
        }

        BeyondCompareReporter::BeyondCompareReporter()
            : GenericDiffReporter(DiffPrograms::Mac::BEYOND_COMPARE())
        {
        }

        KaleidoscopeReporter::KaleidoscopeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::KALEIDOSCOPE())
        {
        }

        SublimeMergeReporter::SublimeMergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::SUBLIME_MERGE())
        {
            launcher.setForeground(true);
        }

        KDiff3Reporter::KDiff3Reporter()
            : GenericDiffReporter(DiffPrograms::Mac::KDIFF3())
        {
        }

        P4MergeReporter::P4MergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::P4MERGE())
        {
        }
        TkDiffReporter::TkDiffReporter()
            : GenericDiffReporter(DiffPrograms::Mac::TK_DIFF())
        {
        }

        CLionDiffReporter::CLionDiffReporter()
            : GenericDiffReporter(DiffPrograms::Mac::CLION())
        {
        }

        MacDiffReporter::MacDiffReporter()
            : FirstWorkingReporter({
                  new AraxisMergeReporter(),
                  new BeyondCompareReporter(),
                  new DiffMergeReporter(),
                  new KaleidoscopeReporter(),
                  new P4MergeReporter(),
                  new SublimeMergeReporter(),
                  new KDiff3Reporter(),
                  new TkDiffReporter(),
                  new VisualStudioCodeReporter(),
                  new CLionDiffReporter()
              })
        {
        }
    }
}

// ******************** From: QuietReporter.cpp

namespace ApprovalTests
{
    bool QuietReporter::report(std::string, std::string) const
    {
        return true;
    }
}

// ******************** From: TextDiffReporter.cpp

#include <iostream>

namespace ApprovalTests
{
    TextDiffReporter::TextDiffReporter()
    {
        std::vector<std::shared_ptr<Reporter>> reporters = {
            CustomReporter::createForegroundReporter("diff"),
            CustomReporter::createForegroundReporter("C:/Windows/System32/fc.exe")};
        m_reporter = std::unique_ptr<Reporter>(new FirstWorkingReporter(reporters));
    }

    bool TextDiffReporter::report(std::string received, std::string approved) const
    {
        std::cout << "Comparing files:" << std::endl;
        std::cout << "received: " << received << std::endl;
        std::cout << "approved: " << approved << std::endl;
        const bool result = m_reporter->report(received, approved);
        if (!result)
        {
            std::cout << "TextDiffReporter did not find a working diff "
                         "program\n\n";
        }

        return result;
    }
}

// ******************** From: WindowsReporters.cpp


namespace ApprovalTests
{
    namespace Windows
    {
        VisualStudioCodeReporter::VisualStudioCodeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::VS_CODE())
        {
        }

        // ----------------------- Beyond Compare ----------------------------------
        BeyondCompare3Reporter::BeyondCompare3Reporter()
            : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_3())
        {
        }

        BeyondCompare4Reporter::BeyondCompare4Reporter()
            : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_4())
        {
        }

        BeyondCompareReporter::BeyondCompareReporter()
            : FirstWorkingReporter(
                  {new BeyondCompare4Reporter(), new BeyondCompare3Reporter()})
        {
        }

        // ----------------------- Tortoise SVN ------------------------------------
        TortoiseImageDiffReporter::TortoiseImageDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_IMAGE_DIFF())
        {
        }

        TortoiseTextDiffReporter::TortoiseTextDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_TEXT_DIFF())
        {
        }

        TortoiseDiffReporter::TortoiseDiffReporter()
            : FirstWorkingReporter(
                  {new TortoiseTextDiffReporter(), new TortoiseImageDiffReporter()})
        {
        }

        // ----------------------- Tortoise Git ------------------------------------
        TortoiseGitTextDiffReporter::TortoiseGitTextDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_GIT_TEXT_DIFF())
        {
        }

        TortoiseGitImageDiffReporter::TortoiseGitImageDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_GIT_IMAGE_DIFF())
        {
        }

        TortoiseGitDiffReporter::TortoiseGitDiffReporter()
            : FirstWorkingReporter(
                  {new TortoiseGitTextDiffReporter(), new TortoiseGitImageDiffReporter()})
        {
        }

        // -------------------------------------------------------------------------
        WinMergeReporter::WinMergeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::WIN_MERGE_REPORTER())
        {
        }

        AraxisMergeReporter::AraxisMergeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::ARAXIS_MERGE())
        {
        }

        CodeCompareReporter::CodeCompareReporter()
            : GenericDiffReporter(DiffPrograms::Windows::CODE_COMPARE())
        {
        }

        SublimeMergeReporter::SublimeMergeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::SUBLIME_MERGE())
        {
            launcher.setForeground(true);
        }

        KDiff3Reporter::KDiff3Reporter()
            : GenericDiffReporter(DiffPrograms::Windows::KDIFF3())
        {
        }

        WindowsDiffReporter::WindowsDiffReporter()
            : FirstWorkingReporter({
                  new TortoiseDiffReporter(), // Note that this uses Tortoise SVN Diff
                  new TortoiseGitDiffReporter(),
                  new BeyondCompareReporter(),
                  new WinMergeReporter(),
                  new AraxisMergeReporter(),
                  new CodeCompareReporter(),
                  new SublimeMergeReporter(),
                  new KDiff3Reporter(),
                  new VisualStudioCodeReporter(),
              })
        {
        }
    }
}

// ******************** From: Scrubbers.cpp

#include <string>
#include <functional>
#include <regex>
#include <map>

namespace ApprovalTests
{
    namespace Scrubbers
    {
        std::string doNothing(const std::string& input)
        {
            return input;
        }
        std::string scrubRegex(const std::string& input,
                               const std::regex& regex,
                               const RegexReplacer& replaceFunction)
        {
            std::string result;
            std::string remainder = input;
            std::smatch m;
            while (std::regex_search(remainder, m, regex))
            {
                auto match = m[0];
                auto original_matched_text = match.str();
                auto replacement = replaceFunction(match);
                result += std::string(m.prefix()) + replacement;
                remainder = m.suffix();
            }
            result += remainder;
            return result;
        }

        Scrubber createRegexScrubber(const std::regex& regexPattern,
                                     const RegexReplacer& replacer)
        {
            return [=](const std::string& input) {
                return scrubRegex(input, regexPattern, replacer);
            };
        }

        Scrubber createRegexScrubber(const std::regex& regexPattern,
                                     const std::string& replacementText)
        {
            return createRegexScrubber(
                regexPattern, [=](const RegexMatch&) { return replacementText; });
        }

        Scrubber createRegexScrubber(const std::string& regexString,
                                     const std::string& replacementText)
        {
            return createRegexScrubber(std::regex(regexString), replacementText);
        }

        std::string scrubGuid(const std::string& input)
        {
            static const std::regex regex("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-["
                                          "0-9a-fA-F]{4}-[0-9a-fA-F]{12}");

            int matchNumber = 0;
            std::map<std::string, int> matchIndices;
            return scrubRegex(input, regex, [&](const RegexMatch& m) {
                auto guid_match = m.str();

                if (matchIndices[guid_match] == 0)
                {
                    matchIndices[guid_match] = ++matchNumber;
                }
                return "guid_" + std::to_string(matchIndices[guid_match]);
            });
        }
    }
}

// ******************** From: ExceptionCollector.cpp

namespace ApprovalTests
{
    void ExceptionCollector::gather(std::function<void(void)> functionThatThrows)
    {
        try
        {
            functionThatThrows();
        }
        catch (const std::exception& e)
        {
            exceptionMessages.emplace_back(e.what());
        }
    }

    ExceptionCollector::~ExceptionCollector()
    {
        if (!exceptionMessages.empty())
        {
            exceptionMessages.emplace_back("ERROR: Calling code forgot to call "
                                           "exceptionCollector.release()");
        }
        release();
    }

    void ExceptionCollector::release()
    {
        if (!exceptionMessages.empty())
        {
            std::stringstream s;
            s << exceptionMessages.size() << " exceptions were thrown:\n\n";
            int count = 1;
            for (const auto& error : exceptionMessages)
            {
                s << count++ << ") " << error << '\n';
            }
            exceptionMessages.clear();
            throw std::runtime_error(s.str());
        }
    }
}

// ******************** From: FileUtils.cpp

#include <fstream>
#include <sys/stat.h>
#include <sstream>

namespace ApprovalTests
{
    bool FileUtils::fileExists(const std::string& path)
    {
        struct stat info
        {
        };
        return stat(path.c_str(), &info) == 0;
    }

    int FileUtils::fileSize(const std::string& path)
    {
        struct stat statbuf
        {
        };
        int stat_ok = stat(path.c_str(), &statbuf);

        if (stat_ok == -1)
        {
            return -1;
        }

        return int(statbuf.st_size);
    }

    void FileUtils::ensureFileExists(const std::string& fullFilePath)
    {
        if (!fileExists(fullFilePath))
        {
            StringWriter s("", "");
            s.write(fullFilePath);
        }
    }

    std::string FileUtils::getExtensionWithDot(const std::string& filePath)
    {
        std::size_t found = filePath.find_last_of('.');
        return filePath.substr(found);
    }

    std::string FileUtils::readFileThrowIfMissing(const std::string& fileName)
    {
        std::ifstream in(fileName.c_str(), std::ios_base::in);
        if (!in)
        {
            throw std::runtime_error("File does not exist: " + fileName);
        }
        std::stringstream written;
        written << in.rdbuf();
        in.close();

        std::string text = written.str();
        return text;
    }

    std::string FileUtils::readFileReturnEmptyIfMissing(const std::string& fileName)
    {
        if (FileUtils::fileExists(fileName))
        {
            return readFileThrowIfMissing(fileName);
        }
        else
        {
            return std::string();
        }
    }

    void FileUtils::writeToFile(const std::string& filePath, const std::string& content)
    {
        std::ofstream out(filePath.c_str(), std::ios::binary | std::ofstream::out);
        if (!out)
        {
            throw std::runtime_error("Unable to write file: " + filePath);
        }
        out << content;
    }
}

// ******************** From: FileUtilsSystemSpecific.cpp

namespace ApprovalTests
{
    std::string FileUtilsSystemSpecific::getCommandLineForCopy(
        const std::string& source, const std::string& destination, bool isWindows)
    {
        if (isWindows)
        {
            return std::string("copy /Y ") + "\"" + source + "\" \"" + destination + "\"";
        }
        else
        {
            return std::string("cp ") + "\"" + source + "\" \"" + destination + "\"";
        }
    }

    void FileUtilsSystemSpecific::copyFile(const std::string& source,
                                           const std::string& destination)
    {
        auto cmd = getCommandLineForCopy(source, destination, SystemUtils::isWindowsOs());
        SystemUtils::runSystemCommandOrThrow(cmd);
    }
}

// ******************** From: MachineBlocker.cpp

namespace ApprovalTests
{
    MachineBlocker::MachineBlocker(std::string machineName_, bool block_)
        : machineName(std::move(machineName_)), block(block_)
    {
    }

    MachineBlocker MachineBlocker::onMachineNamed(const std::string& machineName)
    {
        return MachineBlocker(machineName, true);
    }

    MachineBlocker MachineBlocker::onMachinesNotNamed(const std::string& machineName)
    {
        return MachineBlocker(machineName, false);
    }

    bool MachineBlocker::isBlockingOnThisMachine() const
    {
        const auto isMachine = (SystemUtils::getMachineName() == machineName);
        return isMachine == block;
    }
}

// ******************** From: MoreHelpMessages.cpp

#include <iostream>

namespace ApprovalTests
{
    void MoreHelpMessages::deprecatedFunctionCalled(const std::string& message,
                                                    const std::string& file,
                                                    int lineNumber)
    {
        std::cout << "\n***************** Deprecation Warning: ***************\n"
                  << "*\n"
                  << "* " << message << '\n'
                  << "*\n"
                  << "* Deprecated method:\n"
                  << "*    " << file << ":" << lineNumber << '\n'
                  << "* Called from:\n"
                  << "*    " << ApprovalTestNamer::getCurrentTest().getFileName() << '\n'
                  << "*\n"
                  << "******************************************************\n\n";
    }
}

// ******************** From: StringUtils.cpp

namespace ApprovalTests
{
    std::string StringUtils::replaceAll(std::string inText,
                                        const std::string& find,
                                        const std::string& replaceWith)
    {
        size_t start_pos = 0;
        while ((start_pos = inText.find(find, start_pos)) != std::string::npos)
        {
            inText.replace(start_pos, find.length(), replaceWith);
            start_pos +=
                replaceWith.length(); // Handles case where 'to' is a substring of 'from'
        }
        return inText;
    }

    bool StringUtils::contains(const std::string& inText, const std::string& find)
    {
        return inText.find(find, 0) != std::string::npos;
    }

    std::string StringUtils::toLower(std::string inText)
    {
        std::string copy(inText);
        std::transform(inText.begin(), inText.end(), copy.begin(), [](char c) {
            return static_cast<char>(tolower(c));
        });
        return copy;
    }

    bool StringUtils::endsWith(std::string value, std::string ending)
    {
        if (ending.size() > value.size())
        {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
}

// ******************** From: SystemUtils.cpp

#include <sys/stat.h>

namespace ApprovalTests
{
    bool SystemUtils::isWindowsOs()
    {
#ifdef _WIN32
        return true;
#else
        return false;
#endif
    }

    bool SystemUtils::isCygwin()
    {
#ifdef __CYGWIN__
        return true;
#else
        return false;
#endif
    }

    bool SystemUtils::isMacOs()
    {
#ifdef __APPLE__
        return true;
#else
        return false;
#endif
    }
    std::string SystemUtils::getDirectorySeparator()
    {
        return isWindowsOs() ? "\\" : "/";
    }

    std::string SystemUtils::checkFilenameCase(const std::string& fullPath)
    {
        if (!isWindowsOs() || !FileUtils::fileExists(fullPath))
        {
            return fullPath;
        }
#ifdef _WIN32

        _finddata_t findFileData;
        auto hFind = _findfirst(fullPath.c_str(), &findFileData);

        if (hFind != -1)
        {
            const std::string fixedFilename = findFileData.name;
            const std::string fixedPath = StringUtils::replaceAll(
                fullPath, StringUtils::toLower(fixedFilename), fixedFilename);
            _findclose(hFind);
            return fixedPath;
        }

#endif
        return fullPath;
    }

    std::string SystemUtils::safeGetEnvForWindows(const char* name)
    {
        APPROVAL_TESTS_UNUSED(name);
#ifdef _WIN32
        // We use getenv_s on Windows, as use of getenv there gives:
        //      warning C4996: 'getenv': This function or variable may be unsafe. Consider using _dupenv_s instead.
        //      To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

        size_t size;
        getenv_s(&size, nullptr, 0, name);

        if (size != 0)
        {
            std::string result;
            result.resize(size);
            getenv_s(&size, &*result.begin(), size, name);
            result.pop_back();
            return result;
        }
#endif
        return std::string();
    }

    std::string SystemUtils::safeGetEnvForNonWindows(const char* name)
    {
        APPROVAL_TESTS_UNUSED(name);
        char* p = nullptr;
#ifndef _WIN32
        p = getenv(name);
#endif
        return (p != nullptr) ? p : std::string();
    }

    std::string SystemUtils::safeGetEnv(const char* name)
    {
        return isWindowsOs() ? safeGetEnvForWindows(name) : safeGetEnvForNonWindows(name);
    }

    std::string SystemUtils::getMachineName()
    {
        auto name = safeGetEnv("COMPUTERNAME");
        if (!name.empty())
        {
            return name;
        }

        name = safeGetEnv("HOSTNAME");
        if (!name.empty())
        {
            return name;
        }

        return "Unknown Computer";
    }

    void SystemUtils::makeDirectoryForWindows(const std::string& directory)
    {
        APPROVAL_TESTS_UNUSED(directory);
#ifdef _WIN32
        int nError = _mkdir(directory.c_str());
        if (nError != 0)
        {
            std::string helpMessage =
                std::string("Unable to create directory: ") + directory;
            throw std::runtime_error(helpMessage);
        }
#endif
    }

    void SystemUtils::makeDirectoryForNonWindows(const std::string& directory)
    {
        APPROVAL_TESTS_UNUSED(directory);
#ifndef _WIN32
        mode_t nMode = 0733; // UNIX style permissions
        int nError = mkdir(directory.c_str(), nMode);
        if (nError != 0)
        {
            std::string helpMessage =
                std::string("Unable to create directory: ") + directory;
            throw std::runtime_error(helpMessage);
        }
#endif
    }

    void SystemUtils::makeDirectory(const std::string& directory)
    {
        makeDirectoryForWindows(directory);
        makeDirectoryForNonWindows(directory);
    }

    void SystemUtils::ensureDirectoryExists(const std::string& fullFilePath)
    {
        if (!FileUtils::fileExists(fullFilePath))
        {
            makeDirectory(fullFilePath);
        }
    }

    void SystemUtils::runSystemCommandOrThrow(const std::string& command)
    {
        int exitCode = system(command.c_str());

        if (exitCode != 0)
        {
            throw std::runtime_error(command + ": failed with exit code " +
                                     std::to_string(exitCode));
        }
    }
}

// ******************** From: ExistingFile.cpp

namespace ApprovalTests
{
    std::string ExistingFile::scrub(std::string fileName, const Options& options)
    {
        if (options.isUsingDefaultScrubber())
        {
            return fileName;
        }
        auto content = FileUtils::readFileThrowIfMissing(fileName);
        const auto scrubbedContent = options.scrub(content);
        if (content == scrubbedContent)
        {
            deleteScrubbedFile = false;
            return fileName;
        }
        else
        {
            std::size_t found = fileName.find_last_of('.');
            auto fileExtension = fileName.substr(found);
            std::string baseName = fileName.substr(0, found);

            auto newFileName = baseName + ".scrubbed.received" + fileExtension;
            FileUtils::writeToFile(newFileName, scrubbedContent);
            deleteScrubbedFile = true;
            return newFileName;
        }
    }

    ExistingFile::ExistingFile(std::string filePath_, const Options& options)
    {
        filePath = scrub(filePath_, options);
    }

    std::string ExistingFile::getFileExtensionWithDot() const
    {
        return FileUtils::getExtensionWithDot(filePath);
    }

    void ExistingFile::write(std::string) const
    {
        // do nothing
    }

    void ExistingFile::cleanUpReceived(std::string receivedPath) const
    {
        if (deleteScrubbedFile && (receivedPath == filePath))
        {
            remove(receivedPath.c_str());
        }
    }

    ExistingFileNamer ExistingFile::getNamer()
    {
        return ExistingFileNamer(filePath);
    }
}

// ******************** From: StringWriter.cpp

#include <utility>
#include <fstream>

namespace ApprovalTests
{
    StringWriter::StringWriter(std::string contents, std::string fileExtensionWithDot)
        : s(std::move(contents)), ext(std::move(fileExtensionWithDot))
    {
    }

    std::string StringWriter::getFileExtensionWithDot() const
    {
        return ext;
    }

    void StringWriter::write(std::string path) const
    {
        std::ofstream out(path.c_str(), std::ofstream::out);
        if (!out)
        {
            throw std::runtime_error("Unable to write file: " + path);
        }
        this->Write(out);
        out.close();
    }

    void StringWriter::Write(std::ostream& out) const
    {
        out << s << "\n";
    }

    void StringWriter::cleanUpReceived(std::string receivedPath) const
    {
        remove(receivedPath.c_str());
    }
}
#endif // APPROVAL_TESTS_INCLUDE_CPPS

#endif // APPROVAL_TESTS_CPP_APPROVALS_HPP
